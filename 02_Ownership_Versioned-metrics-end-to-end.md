# 02 · Ownership: Versioned metrics end to end

**Lead:** S1 · **Backup:** S7

**Angle to stress (07):** End to end, design → launch (M0–M7). S7 = owning my own mistake

> Copied on 2026-11-04 from `03_star_stories.md`: hook, STAR points, spoken scripts and 60-second versions only. Follow-ups and weak spots stay in 03. Later edits to 03 won't show up here.

| Story | Role | Status (03 index) | Before you use it |
|---|---|---|---|
| S1 · Versioned-object metrics for Uber: owning a customer feature end to end | Lead | 🟢 |  |
| S7 · My Java 17 upgrade caused a performance regression (failure #1) | Backup | 🟢 release slipped | Use only one S7 version per loop (03). |

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

## Backup · S7 · My Java 17 upgrade caused a performance regression (failure #1)

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
