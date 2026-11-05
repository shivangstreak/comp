# 07 · Insist on the Highest Standards: Index Shrink safety

**Lead:** S2 · **Backup:** S17 · **Backup:** S11

**Angle to stress (07):** Kill switches before the feature; corruption failsafe tested by breaking it

> Copied on 2026-11-04 from `03_star_stories.md`: hook, STAR points, spoken scripts and 60-second versions only. Follow-ups and weak spots stay in 03. Later edits to 03 won't show up here.

| Story | Role | Status (03 index) | Before you use it |
|---|---|---|---|
| S2 · Index Shrink: making database maintenance safe enough to turn back on | Lead | 🟢 zero Sev2s from shrink |  |
| S17 · Soft Delete in OLM: making the one irreversible step impossible to take early | Backup | 🟡 ownership + ship status unconfirmed | Not ready: needs your role and ship status (07). If it didn't ship, tell it as a design story: "I designed it; it was in testing when I left" (03 evidence check). |
| S11 · SQL Server test automation + training (Nutanix) | Backup | 🟢 needs impact |  |

**Notes**
- Out loud, say "a critical customer", not the customer's name (06 avoid list).

---

## Lead · S2 · Index Shrink: making database maintenance safe enough to turn back on

**Hook:** Index rebuilds on our metadata databases had caused **10 auto-cuts and 11 Sev2s** in 2–3 months and were paused in our two biggest regions. I designed an in-place alternative, proved it with production experiments, and rolled it out shard by shard, big regions last.

### Situation & Task (~20%)
- Object metadata lives in **sharded Oracle databases**. Deletes fragment the indexes, measured as **bytesPerRow**. A background job **rebuilt** every partition above bytesPerRow 200. 🟢
- Online rebuilds were expensive and risky: 🟢
  - heavy **TEMP** usage, **~2× space**, **redo spikes**
  - journal tables that often failed to drop, leaving **IOD ticket backlogs**
  - library-cache contention that became **503s for customers**
- Over 2–3 months: **10 auto-cuts and 11 human-cut Sev2s**. Rebuilds were **paused or deferred in IAD and PHX** (OBJMDS-6655). Strategic customers such as Stargate (onboarding) and Uber expect near-zero 503s. 🟢
- **My task:** I owned Index Shrink **end to end**: experiments, design, implementation, testing, ORR, rollout. 🟢
  - Goal: reclaim space on moderately fragmented partitions **without** the rebuild's side effects.
  - Keep rebuild only where it's actually better.

### Action (~60%)
1. **Experiments before design** (May–Aug 2025), on real partitions, including production in EU-PARIS. 🟢
   - Shrink works in two steps: COMPACT (online row movement), then a short space release.

   | Partition | Fragmentation | Shrink (compact + release) | Rebuild |
   |---|---|---|---|
   | 21 GB | bytesPerRow 234 | 14 + 1 min | 14 min |
   | 24.5 GB | 63% deleted | 30 + 1 min | **failed** (OBJMDS-8494) |
   | 24.7 GB | bytesPerRow 402 | 29 + 2 min | 11 min |

   - **Moderate fragmentation:** same time as rebuild, with no TEMP, no journal table and no 2× space.
   - **63% deleted:** rebuild failed; shrink completed.
   - **Heavy fragmentation:** rebuild ~3× faster, so it should stay for that case.
2. **The rule** (after I threw out my first one, see S8): 🟢
   - The ideal bytesPerRow is 200. Up to **+50% (300) → shrink**; above → rebuild.
   - **Configurable per region.**
   - It reuses the rebuild job's existing priority queue, so there's no new scheduler.
3. **Data-integrity failsafe.** 🟢
   - With a DBPerf SME, I **induced index-block corruption** to see what shrink does.
   - On **ORA-01578** it falls back to **exactly one** rebuild from table data: no data loss, no retry loop. A unit test enforces "once".
4. **Blast-radius limits:** 🟢
   - one maintenance operation per CDB at a time
   - a 14-day window per partition
   - an `INDEX_SHRINK_HISTORY` table plus an editioning view, for auditability
5. **Off switches before the feature.** 🟢
   - Global **dry-run** and a **per-shard allow-list**, both JVM args, so rollback needs no deploy.
   - Shipped **dark** in **MDS 5.10 (13 Oct 2025)** to every region, including gov.
   - Enabled in waves: R1/OC16/OC17 (5 Dec), CDG/DXB on a subset of shards (12 Dec), the rest of the non-embargo regions (9 Jan), SJC/ORD and others (16 Jan), then **IAD and PHX last (30 Jan 2026)**.
   - Alarms went out first (17 Dec, 9 Jan).
6. **Getting IAD/PHX back.** Managers had paused rebuilds there. I made the case that shrink removes the specific reasons for that pause. → **S6** 🟢
7. **Review and test.** 🟢
   - Architecture review (Chiranjeeb Buragohain), ECAR (Muralidhar Koka), DBPerf (Jim McCann).
   - I used AI to generate OSTs and automate my test workflow for the change.

### Result + learning
- 🟢 **Measured before launch:** shrink matched rebuild time on moderate fragmentation with **no TEMP, no journal tables and no 2× space**, and completed where **rebuild failed outright**.
- 🟢 **Peak redo ~11× lower** in production on a 36 GB partition: ~11.75 MiB/s for shrink vs ~129.63 MiB/s for a rebuild of the same partition (read from the screenshot legends in `Executive Summary…pdf`; confirm before quoting). See S6 follow-up 13.
- 🟢 **Shipped** to every region, then **enabled small regions first and the big ones last**, including IAD and PHX, where maintenance had been paused.
- 🟢 **Shrink caused zero Sev2s** through the rollout and the months after. It ran cleanly in the smaller regions, then in **IAD and PHX**, where maintenance had been switched off. (your answer)
- **If asked for a fleet-wide before/after number:** *"I don't have a clean fleet-wide before-and-after. What I can tell you is that shrink didn't cause a single Sev2, and index maintenance was running again in our two biggest regions."*
- **Learning:** with production databases, **ship the off switch before the feature**, and let experiments, not intuition, pick the rule.

### Spoken script (2.5–3 min)
> In OCI Object Storage, all object metadata sits in sharded Oracle databases. / When customers delete objects, the indexes fragment, / and a background job rebuilt them. / Those rebuilds were hurting us: / lots of temp space, double the disk space, redo spikes, / and journal tables that failed to clean up. / Over two to three months, rebuilds caused **ten auto-cuts and eleven Sev2s**, / and maintenance was **paused entirely in our two biggest regions**. / And we were onboarding strategic customers who expect almost no 503s.
>
> I owned the alternative, Index Shrink, end to end.
>
> Before designing anything, / I **ran experiments on real partitions**, including in production. / On a moderately fragmented 21-gig partition, / shrink took the same fourteen minutes as a rebuild, / with no temp space, no journal table, no extra disk. / On a partition with sixty-three percent of rows deleted, / **the rebuild failed outright**, / and shrink finished in about thirty minutes. / But on a very fragmented partition, rebuild was three times faster. / So the answer wasn't "replace rebuild". / It was **pick the right tool per partition**: / up to fifty percent above ideal fragmentation, shrink; beyond that, rebuild, / configurable per region.
>
> Because this touches customer metadata, / I spent as much time on safety as on the feature. / With our DB performance expert, I **deliberately corrupted an index block** / to see what shrink would do. / Now, on that corruption error, it falls back to exactly one rebuild from table data, / no data loss, no retry loop. / Only one maintenance operation per container database at a time, / and every operation is recorded.
>
> And I **shipped the off switches before the feature**: / a dry-run flag and a per-shard allow-list, / both changeable without a deploy. / It went out dark to every region in October, / and I enabled it in waves, small regions in December, / and IAD and PHX last, at the end of January, / where I'd had to persuade managers to let maintenance run again.
>
> And the result: / shrink **didn't cause a single Sev2** through the rollout and the months after, / and index maintenance was running again in IAD and PHX, / where it had been switched off.
>
> My takeaway: / with production databases, the off switch ships first, / and experiments, not my intuition, pick the rule.

### 60-second version
> Index rebuilds on our sharded metadata databases had caused **ten auto-cuts and eleven Sev2s** in a couple of months, / and were paused in our two biggest regions. / I owned the alternative, Index Shrink. / Production experiments showed shrink matched rebuild time on moderate fragmentation / with no temp space or journal tables, / and finished even where **a rebuild failed outright**. / So I built a per-partition rule, shrink for moderate fragmentation and rebuild for heavy, / added a corruption failsafe I tested by corrupting an index on purpose, / and shipped it dark with a dry-run switch and a per-shard allow-list, / then enabled it region by region, / **biggest regions last**. / It didn't cause a single Sev2, / and maintenance was running again in our two biggest regions.

---

## Backup · S17 · Soft Delete in OLM: making the one irreversible step impossible to take early

**Hook:** In Object Storage, a delete used to be permanent. Even with versioning, anyone with enough permissions (or ransomware with stolen credentials) could destroy a specific version for good. Soft Delete keeps deleted data recoverable for a window the customer sets. `[CONFIRM: I designed and built]` the lifecycle engine's side: the background processor that **permanently purges** data once that window expires. In a feature built to make deletes safe, the purge is the one step you can't undo.

### Situation & Task (~20%)
- Late 2025 (docs dated Dec 2025) `[NEED: confirm timing]`. Cross-team: web server, MDS, OLM. 🟢
- **Task (OLM side):** find soft-deleted versions whose window has expired and purge them. 🟡 (resume + docs)
  - Never purge early.
  - Never scan the whole fleet.
  - Never disturb existing lifecycle work.

### Action (~60%): the decisions in the OLM design
🟢 = it's in the HLD/LLD · 🟡 = that it was *your* decision, pending your confirmation

1. **Turn lifecycle into two steps, and walk the edge cases.** 🟢 (HLD)
   - User rules soft-delete at their retention; system rules purge after the soft-delete retention.
   - **Manual soft delete before the rule fires:** OLM finds it already soft-deleted, so it does nothing.
   - **Lifecycle retention longer than the soft-delete window:** the version is already purged when the rule fires, so OLM skips it.
2. **Only process buckets that have, *or had*, soft delete.** 🟢 (LLD: the cache counts "enabled" **or** "suspended"; it refreshes when the state changes)
   - **Why "had" matters** 🔵 (from the doc's requirements): a Suspended bucket still holds recoverable versions that must be purged on schedule. If OLM forgot it:
     - the data would never be purged;
     - the customer would keep paying for it;
     - the bucket could never be deleted.
3. **Trust the timestamp, not the policy.** The evaluator compares each version's **own expiry, stamped at delete time**, against the clock. It doesn't recompute from the bucket's current retention. If someone shortens retention later, perhaps a malicious insider, data already deleted keeps its original window. 🟢 (LLD evaluator; design doc: "retention changes are applicable only to newly deleted objects")
4. **Two locks on the irreversible step.** 🟢 (LLD + design doc)
   - OLM purges only after expiry.
   - MDS's `DeleteSoftDeletedObjectVersion` independently **rejects a purge inside the retention window**.
   - The purge also carries **If-Match on the ETag**.
   - So a bug on one side can't delete data early on its own.
5. **Every failure path means "wait", never "delete sooner".** 🟢 (LLD error table)
   - **404:** ignore, since the version is already gone. That makes the purge idempotent.
   - **429 (throttled):** pause and retry later.
   - **500/503:** retry next cycle.
   - Failures are reprocessed in later cycles.
6. **Isolate it from existing lifecycle work.** 🟢 (LLD)
   - Its own scheduled processor and rule target.
   - **Separate thread pools:** lister 2, delete 25, queues of 1,000.
   - Paged listing: 10,000 versions per batch, pages of 2,000.
   - Check whether host shapes need resizing.
   - A **new Embargo (throttling) rule** for the new delete API.
7. **Ship safely and make it observable.** 🟢/🔵 (LLD)
   - Rollout is **gated on MDS shipping first**, and buckets without soft delete are unaffected.
   - Metrics on the flow and its **delay**, plus alarms and Grafana panels.
   - The estimate puts **17 of 28 days on testing** (test plan 2, UT/IT/OST 10, E2E 5) 🔵.

### Result + learning
- `[NEED: did it ship, and when? Bugs caught in testing? Customers using it? If not shipped: the state when you left]`
- **Learning** 🔵 (a suggested framing; keep it only if it's yours): *"For an irreversible operation, store the decision with the data, check it in two independent places, and make every failure path a 'wait', never a 'delete'."*

### Spoken script (~2.5 min), with slots
> In Object Storage, deleting an object used to be permanent. / Versioning helped, but anyone with enough permissions could still delete a specific version for good, / and that's exactly what ransomware does with stolen credentials. / So we built **Soft Delete**: when it's on, a deleted object stays recoverable for a window the customer sets, seven days by default, and only then is it purged.
>
> It was a cross-team feature. / The metadata team moved deleted versions into their own table and stamped each one with its expiry time. / `[CONFIRM: I owned]` the lifecycle engine's side: the background processor that does the **permanent purge**. / In a feature whose whole point is making deletes safe, the purge is the one step you can't take back. / So my bar was: **no bug, retry or config change should ever make it happen early.**
>
> Three decisions came out of that.
>
> First, **trust the timestamp, not the policy.** / The processor checks each version's own expiry, stamped when it was deleted. / If someone later shortens the bucket's retention, even a malicious insider, data that's already deleted keeps its original window.
>
> Second, **two locks on the irreversible step.** / The processor purges only after expiry, / and the metadata service independently rejects a purge inside the window. / A bug on one side can't delete data early on its own. / And every failure, whether throttling or a transient error, means *wait and retry next cycle*, never *delete sooner*.
>
> Third, **don't forget buckets that turned it off.** / We process buckets that have, *or had*, soft delete. / A bucket that suspended it still holds recoverable data that has to be purged on schedule. / Otherwise the customer keeps paying for it, and can't even delete the bucket.
>
> I also gave it its own thread pools, so purges couldn't starve existing lifecycle work, / and planned more than half the effort for testing.
>
> `[Result: shipped when / what testing caught / the state when you left.]`
>
> What I took from it: / for an irreversible operation, **store the decision with the data, check it in two independent places, and make every failure path a wait, never a delete.**

- **Credit line to keep:** "the metadata team" built the table, the APIs and the permissions. Your part is the purge side.
- If it didn't ship, change the result paragraph to the honest state. The design decisions still carry the story.

### 60-second version
> Deleting data in Object Storage used to be permanent, so we built **Soft Delete**: deleted data stays recoverable for a window the customer sets, then gets purged. / `[CONFIRM: I owned]` the purge, the lifecycle engine's background processor, which is the one irreversible step. / I designed it so nothing could make it happen early. / It checks each version's own expiry, stamped at delete time, so shortening the retention later can't shrink the window. / The metadata service independently rejects early purges, so it takes two bugs, not one. / Every failure means retry later, never delete sooner. / And it tracks buckets that *had* soft delete, not just ones that have it, so suspended buckets still get cleaned up. / `[Result.]`

---

## Backup · S11 · SQL Server test automation + training (Nutanix)

**Hook:** Our SQL Server driver had thin automated coverage. I built **~80–90 functional tests** for single-instance and Availability-Group databases, and ran training sessions so the team could extend them.

### Situation & Task (~20%)
- Jan–Mar 2023, Nutanix NDB SQL Server driver team. 🟢 [From memory: why automation was needed then (release quality? manual QA burden? escaped bugs?)]
- I was a senior engineer (MTS-3) and, per my 2023 resume, "managed and mentored a team of 3+ developers". 🟢
- **Task:** build functional-test automation for SQL Server workflows and get the team able to use and extend it. 🟢

### Action (~60%)
1. **Built ~80–90 VDI-based functional tests** covering single-instance and AG databases. 🟢 (weekly status)
2. **Unblocked CI:** fixed a sudo-prompt hang that stalled the pipeline. 🟢
3. **Ran training/KT sessions** on the framework; teammates' status entries cite them. 🟢
4. **Found and fixed a German-locale provisioning bug** (ERA-24536) in the same period. 🟢 [From memory: was it found by your tests?]
5. Mentored interns and juniors on POCs and did code reviews. 🟢 (2023 resume) [From memory: one specific person and what they built]

### Result + learning
- 🟢 ~80–90 automated FTs in about a quarter. Training sessions others relied on.
- [From memory: bugs caught? release-cycle time saved? manual QA reduced? who took over the framework?]
- **Learning:** [From memory. A candidate, if true: "Automation only sticks if others can extend it, so the training mattered as much as the tests."]

### Spoken script (~2 min)
> In early 2023, at Nutanix, / [From memory: why automation was needed.] / I took on building functional-test automation for our SQL Server workflows. / Over about a quarter I built **eighty to ninety tests**, / covering single-instance and Availability Group databases, / and fixed a CI issue where a sudo prompt was hanging the pipeline.
>
> But I didn't want to be the only person who could maintain it. / So I ran **training sessions** on the framework, / how to write a test, how to debug a failure, / and teammates started building on it. / [From memory: one specific person and what they did.]
>
> [From memory: result: bugs caught, cycle time, or who owned it after.]
>
> What I took away: / [From memory.]

### 60-second version
> In early 2023 I built **~80–90 automated functional tests** for our SQL Server workflows, single-instance and Availability Groups, / fixed a CI hang that was blocking the pipeline, / and ran **training sessions** so the team could write and debug tests themselves. / [From memory: result + one mentee example.]
