# 14 · Deliver Results: Versioned metrics in 8 weeks

**Lead:** S1 · **Backup:** S2

**Angle to stress (07):** 8 weeks, shipped in MDS 6.5 for a critical customer

> Copied on 2026-11-04 from `03_star_stories.md`: hook, STAR points, spoken scripts and 60-second versions only. Follow-ups and weak spots stay in 03. Later edits to 03 won't show up here.

| Story | Role | Status (03 index) | Before you use it |
|---|---|---|---|
| S1 · Versioned-object metrics for Uber: owning a customer feature end to end | Lead | 🟢 |  |
| S2 · Index Shrink: making database maintenance safe enough to turn back on | Backup | 🟢 zero Sev2s from shrink |  |

**Notes**
- Out loud, say "a critical customer", not the customer's name (06 avoid list).

---

## Lead · S1 · Versioned-object metrics for Uber: owning a customer feature end to end

**Hook:** Uber, a critical customer moving onto OCI, had no way to see metrics for their versioned objects. I had **8 weeks** to design, build, test and ship two new public metrics for their ~700 buckets, and I did it without touching the object write path.

### Situation & Task (~20%)
- OCI Object Storage published per-bucket **StoredBytes** and **ObjectCount** from a pre-aggregated summary table. There was **nothing for object versions**, so with versioning on, a customer couldn't separate live data from old versions or attribute cost to them. 🟢
- **Uber**, a critical customer **moving onto OCI** with **~700 buckets**, needed this as part of onboarding. Before it, they had **no way to see metrics for versioned objects**. 🟢 (your answer)
- **I had 8 weeks** to design, build, test and ship it. 🟢 (your answer; matches the files: design doc 27 Mar → MDS 6.5 on 26 May 2026)
- I was the **end-to-end owner**: design, DB tuning, the new service, telemetry, tests, ORR and launch (assignee on milestones M0–M7). 🟢
- The hard part: no summary table existed for versions, and **MDS_OBJECT_VERSIONS is sharded**, with one bucket spanning up to 10 shards. So "count the versions" is really a distributed fan-out and reduce. 🟢

### Action (~60%)
1. **I split the problem into two decisions: how to aggregate, and how to publish.**
   - **Aggregation:** the "proper" answer was a pre-aggregated version-usage summary table, but that changes the object **write path** on a system with hundreds of billions of objects.
   - I chose **query-time aggregation**: no write-path risk and faster delivery.
   - I wrote down when to revisit it. By my estimate, 10K buckets concentrated on one heavy shard would take ~22–23 min per run. 🟢
2. **Publishing:** I built a **separate scheduled service** instead of extending the existing telemetry publisher. That kept a heavy aggregation job away from the pipeline that publishes every customer's existing metrics. 🟢
3. **Query design from measurements, not intuition.**
   - In IAD, per-bucket sequential queries took ~13 s for 10 shards. A GROUP BY over 12 buckets took ~2 s (≈6 buckets/s vs 0.77): **~8× throughput**.
   - I opened **DBPERF-15959** and worked through query plans with DBPerf. PARALLEL 4 saved only ~0.4 s over PARALLEL 2 for more DB resources, so I kept 2. 🟢
4. **Execution model:**
   - **One worker per shard**, so no two threads ever hit the same shard.
   - Within a shard, sequential batches of **15 bucket IDs**; a pool of **10** threads; results merged in a ConcurrentHashMap and summed across shards. 🟢
5. **Correctness over coverage.** I designed it to **never publish a wrong number**. 🟢
   - If any shard for a bucket fails or times out, that bucket is skipped, not published as partial or zero.
   - The blackout check **fails closed**, and a lease-gated single publisher prevents duplicate publishes.
   - An alarm fires if fewer than **95%** of buckets publish.
6. **Cross-team dependency.** T2 had to whitelist the two new metric names. I filed **TEL-23840** during design so it ran in parallel instead of becoming the critical path. 🟢 [From memory: any friction or delay with T2?]
7. **Operational readiness:**
   - **48 unit tests + an end-to-end OST** covering missing buckets, timeouts and fail-closed blackout.
   - A Grafana dashboard, a runbook, P1–P3 alarms, and an ORR.
   - Launched as **LA for Uber only**. 🟢
   - [Optional bridge to S9: the juniors took implementation tasks; a teammate built the tenant-DB mapping piece.]

### Result + learning
- 🟢 Shipped in **MDS 6.5 (26 May 2026)**, **inside the 8-week window**. LA for Uber's ~700 buckets.
- 🔵 Daily run on Uber's heaviest shard: by my design estimate, **~1.5 min warm and ~2.7 min cold** (47 batches × 2 s; 69 s + 46 × 2 s). That's trivial against a 24-hour cycle.
- 🟢 **Zero** change to the object write path or the existing telemetry pipeline.
- 🟢 **Uber was happy.** For the first time they could see version count and version storage per bucket. That mattered for onboarding a critical customer moving onto OCI. (your answer)
- **Learning:** ship the design that's safe now, and write down the number that tells you when to change it.

### Spoken script (2.5–3 min)
> Uber is a critical customer that was moving onto OCI Object Storage, / with about seven hundred buckets, many of them versioned. / We published bucket metrics like stored bytes and object count, / but nothing that separated live data from old versions. / So they couldn't see what their versions were costing them.
>
> I owned the fix end to end: / design, database tuning, a new service, telemetry, tests, and launch. / And I had **eight weeks** to do all of it, / because it was part of getting them onboarded.
>
> The first real decision was **how to compute the numbers**. / The textbook answer is a pre-aggregated summary table, updated on every write. / But that means changing the object write path, on a system with hundreds of billions of objects, / for one customer's request. / So I chose **query-time aggregation**: / no write-path risk, and much faster to deliver. / And I wrote down when we'd need to revisit it. / By my estimate, ten thousand buckets on one heavy shard would take around twenty-two minutes, / and the design says that if adoption grows past that, the summary table is the way to go.
>
> The catch is that version data is **sharded**, / and one bucket can span up to ten shards. / So I designed it as a fan-out and reduce: / one worker per shard, so no shard ever gets hit by two threads, / small batches of fifteen buckets, / and a merge across shards. / I didn't guess the query, either. / I measured it in IAD: / a GROUP BY over a batch gave about **eight times** the throughput of per-bucket queries, / and I worked the plan through with our DB performance team.
>
> The part I cared most about was **never publishing a wrong number**. / If any shard for a bucket fails, / we skip that bucket. We don't publish a partial count that looks real. / The blackout check fails closed, / and there's an alarm if coverage drops below ninety-five percent.
>
> The two new metric names needed whitelisting by the telemetry team, / so I filed that ticket during design, / and it ran in parallel instead of blocking launch. / I added forty-eight unit tests and an end-to-end test, / a dashboard, a runbook and alarms, / and took it through operational readiness review.
>
> It shipped in our May release, **inside the eight weeks**, / as a limited release for Uber. / On their heaviest shard a daily run takes about two to three minutes, / with zero change to the write path. / And Uber was happy: for the first time, they could see what their versions were costing them.
>
> What I took away: / pick the design that's safe to ship now, / and write down the number that tells you when it's time to change it.

### 60-second version
> Uber, a critical customer moving onto OCI, had no way to see metrics for their versioned objects, / and I had **eight weeks** to fix that, end to end. / Instead of changing the object write path to maintain a summary table, / I chose query-time aggregation, / and documented the scale point where we'd switch. / Version data is sharded, / so I built a fan-out and reduce, one worker per shard, / tuned the query with our DB performance team for about **8× throughput**, / and made it **fail closed**: / if any shard fails, we skip the bucket rather than publish a wrong number. / I got the telemetry dependency moving during design, / added 48 unit tests, an end-to-end test, alarms and a runbook, / and shipped it **inside the eight weeks**, / for Uber's ~700 buckets, with zero write-path change.

---

## Backup · S2 · Index Shrink: making database maintenance safe enough to turn back on

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
