# 03 · Invent and Simplify: Index Shrink in place

**Lead:** S2 · **Backup:** S9

**Angle to stress (07):** Shrink in place: no TEMP, no second copy. S9: slow down per shard instead of a 1-hour pause

> Copied on 2026-11-04 from `03_star_stories.md`: hook, STAR points, spoken scripts and 60-second versions only. Follow-ups and weak spots stay in 03. Later edits to 03 won't show up here.

| Story | Role | Status (03 index) | Before you use it |
|---|---|---|---|
| S2 · Index Shrink: making database maintenance safe enough to turn back on | Lead | 🟢 zero Sev2s from shrink |  |
| S9 · Designing OLM's per-shard rate limiting and growing my mentee to SD2 through it | Backup | 🟢 (design: you said) |  |

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

## Backup · S9 · Designing OLM's per-shard rate limiting and growing my mentee to SD2 through it

**Hook:** My mentee needed high-impact work to move from SD1 to SD2. I designed per-shard adaptive rate limiting for our lifecycle engine, handed them the build, and coached them through it, reviewing with questions instead of fixes. It shipped, and they were promoted.

### Situation & Task (~20%)
- **OLM** runs customers' lifecycle rules, such as "delete versions older than 30 days", by sending deletes to the metadata service's database shards. 🟢
- When MDS throttled it (429/503/403), OLM **stopped processing that bucket's shard for one hour**, then resumed at full speed. 🟢
  - The result was **burst, then wait, then burst**: capacity sat unused for an hour, then the burst triggered throttling again.
  - Lifecycle cycles slowed down.
  - The upcoming batch-delete Embargo redesign was going to send OLM **more** 429s, and the OLM team had committed to adapting. 🟢
- I had **two junior engineers** working with me across MDS/OLM projects. **One was SD1 and needed impactful, visible work to make the case for SD2.** 🟢 (your answer)
- **Task:** design the fix, and use it to grow my mentee. They build it; I'm accountable for the design and for it working in production.

### Action (~60%)
1. **The design: throttle at the unit that's actually the bottleneck.** 🟢 (commit messages, `RateLimiterController`, `base.conf`)
   - One rate limiter **per (tenant namespace, database shard)**, applied only to lifecycle **deletes**. The shard is what overloads; one tenant spans many shards, and tenants share shards.
   - **Adaptive**, evaluated in **5-second windows**:
     - if successes used **≥80% of the allowance**, raise the rate **×1.2** (cap 10,000/s)
     - if **≥20%** of requests failed, cut it **×0.8** (floor 100/s)
     - otherwise hold. It starts at 100/s.
   - **No more one-hour pause** for enabled tenants. A throttled shard slows down; every other shard keeps working.
   - **Fair pickup** (CASPER-48918): shards are picked uniformly each versioned cycle, and the share of a tenant's buckets processed per cycle is configurable.
   - **Enabled per tenant** in config, so it could roll out tenant by tenant. The per-shard rate is published as a metric.
2. **Handed over the problem, not just tickets.** 🟢 I walked my mentee through *why*: the burst-wait-burst loop, and why the shard rather than the tenant is the unit. Then they owned the implementation end to end; both tickets are theirs in git.
3. **Reviewed with questions, not fixes.** 🟢 (your answer) Instead of rewriting their code, I asked questions that made them find the gap themselves.
   - **My concrete scene.** I found this flaw; the fix is in git:
     - The first version computed success as successes ÷ requests sent.
     - So a shard with **no traffic** in a window counted as 0% success and **got its limit cut**.
     - A lightly used shard where everything succeeded kept **ratcheting up toward 10,000/s**, a rate it had never tested. The burst problem would come straight back.
     - The April change measures success **against the allowance**, cuts only on real failures, and otherwise holds. 🟢 (diff of 9 Apr 2025)
4. **Testing as part of the job.** 🟢 They wrote a dedicated rate-limiter test suite (`RateLimiterTests`, ~200 lines). I reviewed the scenarios with them.
5. **Made the impact visible as theirs.** 🟢 (your answer) I guided them on framing the work for their SD2 case: the problem, the design trade-offs and the result.
6. **The second junior, across the Java 17 upgrade, paginated GET and Uber metrics:** I gave them ownership of test phases, reviewed results with them, and coached their status updates: what's done, what's at risk, what they need. 🟢

### Result + learning
- 🟢 **Shipped** (Mar 2025, refined Apr 2025). OLM now slows down per shard instead of pausing buckets for an hour, enabled tenant by tenant.
- 🟢 **My mentee was promoted from SD1 to SD2** in the **August 2025** review cycle, with this as their impactful work. (your answer)
- **Learning:** the fastest way to grow someone is **a problem with real stakes and a clear design boundary**. Then review with questions, so the insight is theirs.

### Spoken script (2.5–3 min)
> One of the two junior engineers I mentored at Oracle was at SD1, / and to make the case for SD2 they needed **impactful work of their own**, not just tickets on my projects. / Around then, our lifecycle engine had a real problem, / and I saw a chance to solve both.
>
> The lifecycle engine runs customers' rules, like "delete versions older than thirty days", / by sending deletes to our metadata database shards. / Whenever a shard throttled it, / it **paused that bucket for a full hour**, / then came back at full speed. / So we'd burst, get throttled, sit idle for an hour, and burst again. / And an upcoming change to our rate limiter was about to throttle it *more*.
>
> I designed the fix. / The key idea: **throttle at the unit that actually overloads, the database shard**, not the tenant. / Each tenant-and-shard pair gets its own rate limiter for deletes. / Every five seconds it adapts: / if we used most of our allowance successfully, go up twenty percent; / if a fifth of requests failed, come down twenty percent; / otherwise hold, with a floor and a ceiling. / No more hour-long pauses: a throttled shard slows down, and every other shard keeps working. / And it's enabled tenant by tenant, so we could roll it out safely.
>
> Then I handed it to my mentee. / I walked them through **why** the design looked that way, / and they owned the implementation and the tests end to end.
>
> In reviews, I asked questions instead of writing fixes. / The one I remember: I'd spotted a flaw in their first version, / so I asked: "what happens to the limit on a shard that gets **no traffic** for a window?" / Their first version measured success as a share of requests sent, / so an idle shard looked like a failing shard and got cut, / and a lightly used shard kept ratcheting up to a rate it had never tested. / They worked it out and changed it to measure success **against the allowance**.
>
> It shipped, / the lifecycle engine stopped pausing buckets for an hour, / and **my mentee was promoted to SD2** in the next review cycle, with this as their impact work. / I also coached them on telling that story: the problem, the trade-offs, the result.
>
> What I took away: / the fastest way to grow someone is a problem with **real stakes and a clear boundary**, / and reviews that ask questions, so the insight is theirs.

### 60-second version
> One of my two mentees at Oracle needed impactful work to move from **SD1 to SD2**. / Our lifecycle engine paused a bucket for **an hour** whenever a database shard throttled it, then burst again. / I designed the fix: a rate limiter **per tenant and shard**, adapting every five seconds, up when we used our allowance successfully, down on failures, with no hour-long pauses. / I handed my mentee the build, explained the *why*, / and **reviewed with questions instead of fixes**, / which is how they caught that an idle shard was being treated like a failing one. / It shipped, and **they were promoted to SD2**. / Real stakes plus a clear design boundary grows people fastest.
