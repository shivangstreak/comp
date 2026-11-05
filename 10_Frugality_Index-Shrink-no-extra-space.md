# 10 · Frugality: Index Shrink no extra space

**Lead:** S2 · **Backup (stack):** S1 · **Backup (stack):** S7

**Angle to stress (07):** No extra space in capacity-short regions; reused the rebuild queue. Stack S1 (no new table) and S7 (two JVM flags)

> Copied on 2026-11-04 from `03_star_stories.md`: hook, STAR points, spoken scripts and 60-second versions only. Follow-ups and weak spots stay in 03. Later edits to 03 won't show up here.

| Story | Role | Status (03 index) | Before you use it |
|---|---|---|---|
| S2 · Index Shrink: making database maintenance safe enough to turn back on | Lead | 🟢 zero Sev2s from shrink |  |
| S1 · Versioned-object metrics for Uber: owning a customer feature end to end | Backup (stack) | 🟢 |  |
| S7 · My Java 17 upgrade caused a performance regression (failure #1) | Backup (stack) | 🟢 release slipped | Use only one S7 version per loop (03). |

**Notes**
- ⚠️ Weak LP. From 04 §4, stack three quick ones in a single answer: S1 (no new table, no write-path change), S2 (reused the rebuild job's priority queue; no new scheduler), S7 (fixed with two JVM flags, no code change).
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

## Backup (stack) · S1 · Versioned-object metrics for Uber: owning a customer feature end to end

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

## Backup (stack) · S7 · My Java 17 upgrade caused a performance regression (failure #1)

**Hook:** I owned moving our lifecycle service from Java 8 to 17. It compiled and passed tests, and then perf2 showed a regression that took me **about 8 weeks** to pin on a TLS default that wasn't on anyone's checklist.

### Situation & Task (~20%)
- 2024. **OLM** (Object Lifecycle Management) is the service that runs customers' lifecycle rules (deletes, archival) across the fleet. 🟢
- Platform mandates landed together: 🟢
  - **Prism** adoption (CASPER-34390)
  - **Jipher** FIPS-validated crypto (CASPER-34392), March 2024
  - **Java 8 → 17** (CASPER-36221), April–July 2024
- **I owned the Java 8 → 17 upgrade across our MDS services**, each with its own challenges (your answer of 2026-11-02; the git trail you have is OLM's) `[NEED: which services]`. Two juniors helped (→ S9). Task: upgrade without regressions, qualify it, roll it out. 🟢

### Action (~60%)
1. **Did the migration.** 🟢 (your commits)
   - Prism and Jipher changes (14 Mar)
   - Java 17 code changes (22 Apr)
   - the right Guice version (19 Jun)
   - `--add-exports`/`--add-opens` across every app and script (30 Jun)
   - aligned casper-shared, WebServer-v2 and MDS client versions (2 Jul)
2. **Then perf2 load testing showed a bad latency regression** against the Java 8 baseline, bad enough that **we held the rollout**. 🟢 (your answer)
3. **Went after it systematically.** 🟢 (commit of 30 May: "Debugging perf2 issue")
   - From **30 May** I added targeted logging.
   - I **skipped ITs in the PR build** so each perf iteration produced a tag faster.
4. **Found the root cause:** the newer **TLS session-ticket** mechanism, combined with the Jipher crypto provider, made every session resumption run a **full TLS handshake**, which is computationally expensive. 🟢 (commit message)
5. **Fixed it in configuration, not code (24 Jul):** 🟢
   - `-Djdk.tls.client.enableSessionTicketExtension=false`, to fall back to session IDs
   - `-Djdk.tls.namedGroups=secp256r1,secp384r1,secp521r1`, restricting named groups to ones Jipher supports
   - then upgraded the ODO base image (13 Aug)
6. **A second detour: the garbage collector.** 🟢 (your answer of 2026-11-02)
   - We switched from **G1** (the JDK 17 default) to **ZGC**, the low-pause collector. `[NEED: why. Lower GC pauses for tail latency?]`
   - In perf2 it caused **CPU spikes and a throughput drop**, so we **switched back to G1 by configuration**. We did **not** roll back to Java 8. The GC change still meant a **re-qualification**. 🟢 (your answer of 2026-11-02)
   - Likely reasons to offer *only as reasoning*: in JDK 17, ZGC is **not generational**, so with high allocation rates it re-scans the whole heap each cycle. Its load barriers cost CPU on every reference read. If it can't keep up with allocation, threads hit **allocation stalls**. Generational ZGC only arrived in JDK 21.

### Result + learning
- 🟢 Caught in **perf2 load testing, not production**. Latency was bad enough that we **held the rollout**. (your answer)
- 🟢 **The release slipped.** Reasons (your answers of 2026-11-01/02):
  1. **The TLS hunt:** ~8 weeks from the first debugging build (30 May) to the fix (24 Jul 2024), then a **full re-qualification**.
  2. **The GC detour:** G1 → ZGC caused CPU spikes and a throughput drop, so we went back to G1 by config, then **re-qualified**. `[NEED: rough dates]`
  3. **Several MDS services**, each with its own breakages, plus **three platform mandates** (Prism, Jipher, Java 17) landing at once.
- 🔵 About **8 weeks** from the first debugging commit (30 May) to the fix (24 Jul).
- 🟢 Fixed with two JVM args, no code change, then shipped.
- **Learning:** load testing in a test environment did its job; that's why we do it (your words). My miss was finding it at the **end**, which turned a config fix into a release slip. Now, for any runtime or crypto upgrade:
  - I run the perf comparison **early**, against a baseline taken before the change, not only at the final gate.
  - I read release notes for **changed defaults** (TLS, GC, networking), not just removed APIs. *(Say these only if they're true for you.)*

### Spoken script (2.5–3 min)
> In 2024, I owned upgrading our Object Lifecycle service from Java 8 to 17. / That's the service that runs customers' lifecycle rules, deleting and archiving objects across the fleet. / It landed together with two other platform mandates: / a new deployment platform, and a FIPS-certified crypto library called Jipher.
>
> The code side went fine. / I fixed the API breaks, the module access flags, the dependency versions. / It compiled, the tests passed. / And then **perf2 load testing showed a bad latency regression** against our Java 8 baseline, / bad enough that we held the rollout.
>
> This is the part I own. / My test plan answered "does it compile and pass tests". / It **didn't answer "does it behave the same under load"**. / I hadn't treated the runtime itself as something that could change behaviour.
>
> So I went after it methodically. / I added targeted logging, / and I sped up the loop. I skipped integration tests in the PR build / so each perf experiment got a build faster. / It took a while. / Nothing in the code had changed in the hot path. / Eventually I found it in the **TLS layer**: / the newer Java versions use a session-ticket mechanism for resuming TLS sessions, / and with the Jipher provider, / **every resumption was doing a full handshake**, / which is expensive. / The fix turned out to be two JVM flags: / turn off session tickets and use session IDs, / and restrict the key-exchange groups to ones Jipher supports.
>
> It was caught before production, / but from my first debugging build to the fix was about **eight weeks**, / and because the fix meant **re-qualifying the release**, / our rollout slipped.
>
> What I changed after that: / for runtime or crypto upgrades, / I take a performance baseline **before** touching anything, / and "no regression against baseline" is an exit criterion, not something I find out at the end. / And I read release notes for **changed defaults**, / not just removed APIs, / because the defaults are what bite you.

### 60-second version
> I owned upgrading our lifecycle service from Java 8 to 17, / alongside a move to a FIPS crypto library. / It compiled and passed tests, / then **perf2 load testing showed a bad latency regression**. / My miss: my plan checked compatibility, not behaviour under load. / I instrumented it, sped up the build loop to iterate, / and after about **eight weeks** found it in the TLS layer: / newer session tickets plus the new crypto provider meant **every resumption did a full handshake**. / Two JVM flags fixed it before production, but re-qualifying **slipped the release**. / Since then, I baseline performance **before** any runtime upgrade / and check release notes for changed defaults.
