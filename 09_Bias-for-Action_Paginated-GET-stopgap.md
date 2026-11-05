# 09 · Bias for Action: Paginated GET stopgap

**Lead:** S3 · **Backup:** S1

**Angle to stress (07):** Stopgap (Embargo + runbook) shipped while I designed the real fix

> Copied on 2026-11-04 from `03_star_stories.md`: hook, STAR points, spoken scripts and 60-second versions only. Follow-ups and weak spots stay in 03. Later edits to 03 won't show up here.

| Story | Role | Status (03 index) | Before you use it |
|---|---|---|---|
| S3 · Paginated GET: stopping one tenant's huge downloads from hurting everyone | Lead | 🟢 |  |
| S1 · Versioned-object metrics for Uber: owning a customer feature end to end | Backup | 🟢 |  |

**Notes**
- Out loud, say "a critical customer", not the customer's name (06 avoid list).

---

## Lead · S3 · Paginated GET: stopping one tenant's huge downloads from hurting everyone

**Hook:** One tenant's GETs on a single 281 GB object pushed **~2.6 million chunk-row reads per second** into a metadata shard and caused **~30% 503s**. I redesigned GET so every metadata call does bounded work, **at most 100 chunks**, which also made throttling meaningful.

### Situation & Task (~20%)
- **NOC-181566, 20 Mar 2025, AMS.** One tenant (Cloudflare) sent **~260 GETs/s for 165 min (2.6 M total)** on a **281 GB object with 9,935 chunks**, dropping each connection within about a second. 🟢
- Every GET loaded the object's **entire chunk list** from MDS, which meant: 🟢
  - **~2.6 M chunk rows/s**
  - **20% of DB reads over 2 s**
  - **~30% 503s**, other tenants included
- **Third time from the same tenancy:** NOC-177936 (3 Sep 2024) and NOC-178509 (28 Sep 2024) were range reads averaging ~6,000 chunks per object. Both were mitigated by embargo rules on the customer's bucket. 🟢
- Existing throttling **counted requests, not work**. At 100 RPS on a 10K-chunk object, that's **1 M chunk reads/s** with no rule firing. 🟢
- **My task:** design, build and ship the fix across **MDS and the Web Server**. 🟢

### Action (~60%)
1. **Named the root cause.** The cost of one GET grew with the object's chunk count, with no upper bound. A range-read enhancement already in progress (OCCAPA-66714 / CASPER-6745: select only the chunks a range needs) **wouldn't help** a full GET, or a large range. 🟢
2. **Proposed a fix in three parts, plus a stopgap.** 🟢
   - **Range reads** → the range-read enhancement (right for legitimate range GETs).
   - **Full GETs** → pagination.
   - **Throttling** → chunk-aware, via fixed work per call.
   - **Meanwhile**, a short-term remediation: proactively embargo high-chunk objects in that tenancy, and update runbooks.
3. **MDS design:** each call returns **at most 100 chunks** (configurable) plus an **opaque token with the etag embedded**. If the object is modified mid-download, the next page fails cleanly instead of mixing versions. 🟢
4. **Made throttling mean something.** 🟢 (doc's worked example)
   - With a 10/s per-tenant limit on a 10K-chunk object, today's design allows **100K chunk reads/s**. With 100-chunk pages, MDS caps it at **1,000/s** and returns 429s.
   - Caveat I flagged: a 429 **can't be sent after a 200** has started streaming, so the Web Server has to drop the connection. Throttling has to land on page fetches.
5. **Web Server design (Vert.x):** 🟢
   - The event loop streams data; worker threads fetch the next page from MDS.
   - Switching between the event loop and worker threads **many times in one request was a new pattern** in the codebase, so **I built a small standalone project to prove it safe** before relying on it.
   - **Prefetching** the next page while the current one streams avoids pauses that could cause client **read timeouts**. That was scoped as an incremental optimisation, not a first-release must.
6. **Rejected byte-range pagination** (reuse range-GET code, no MDS change): with byte ranges, MDS work per call depends on how the customer uploaded the object, i.e., its chunk sizes. Chunk-count pages make it fixed by construction. 🟢
7. **Named the costs honestly:** 🟢
   - 1 MDS call becomes ~100 for a 10K-chunk object (more DB queries).
   - Higher throttling odds for that pattern, so the public docs need updating.
   - Page size to be **calibrated by testing query latency against page size**.
   - Ship **behind a feature flag**, with scale/perf testing across load types.
   - I used AI to generate OSTs and automate the test workflow.

### Result + learning
- 🔵 **By design:** for the incident object, rows per MDS call drop from **9,935 to at most 100**, about **99% less metadata work per request** (your resume figure). Per-tenant load becomes cappable (100K → 1,000 chunk reads/s in the worked example).
- 🟢 Shipped around **March–April 2026** (your answer), page size 100, configurable. **Time to first byte improves**, because the first page arrives without loading the full chunk list.
- **Learning:** in a multi-tenant system, **no single request's cost should scale with one customer's data**. Bound the work per call, and throttling becomes fair almost for free.

### Spoken script (2.5–3 min)
> We had an incident in our Amsterdam region. / One tenant was downloading a single 281-gigabyte object, / about ten thousand chunks, / at around 260 requests a second for nearly three hours. / The problem: **every GET loaded the full chunk list** from the metadata database. / So we were reading about **2.6 million rows a second** from one shard, / and about **thirty percent of requests got 503s**, / including other customers. / It was the **third time** from the same tenancy. / And our throttling didn't fire, because it **counted requests, not work**. / 260 requests a second looks normal; 2.6 million row reads doesn't.
>
> I owned the fix across the metadata service and the web server.
>
> The root cause was that **one request's cost scaled with the customer's data, with no upper bound**. / A range-read improvement was already in progress, / but it wouldn't help a full GET. / So I proposed a fix in three parts: / the range-read work for range GETs, / pagination for full GETs, / and throttling that reflects real work. / And while we built it, / we embargoed high-chunk objects in that tenancy and updated runbooks.
>
> In the design, / each metadata call returns **at most a hundred chunks**, / plus a token for the next page with the object's **etag inside**, / so if the object changes mid-download, / the next page fails cleanly instead of mixing two versions.
>
> That fixed cost is what makes throttling fair. / With a limit of ten calls a second, / a ten-thousand-chunk object used to allow a hundred thousand row reads a second. / With pages, it's capped at a thousand.
>
> On the web server, / the event loop streams data while worker threads fetch the next page. / Hopping between those threads many times in one request / was **a new pattern** in our codebase, / so I built a small standalone project to prove it safe first.
>
> There was a simpler option: paginate by byte range and reuse existing code. / I argued against it, / because then database work per call depends on how the customer uploaded the object, / which is exactly the problem we were fixing.
>
> By design, / each call now reads at most a hundred rows instead of almost ten thousand, / about **ninety-nine percent less per request**, / and the first byte arrives sooner.
>
> What I took away: / in a multi-tenant system, / don't let one request's cost scale with one customer's data. / Bound the work, and fair throttling follows.

### 60-second version
> A single tenant hammered a 281-gig object, / and because **every GET loaded the full chunk list**, / we read 2.6 million rows a second from one shard, / and about **30% of requests got 503s**, other tenants included. / Throttling didn't fire because it **counted requests, not work**. / I owned the fix: / each metadata call now returns **at most 100 chunks**, with an etag-bearing token so a mid-download overwrite fails cleanly. / That fixed cost makes throttling fair: / a ten-calls-a-second limit now caps a tenant at a thousand row reads, not a hundred thousand. / I proved the new event-loop threading pattern with a standalone POC, / rejected byte-range pagination because it didn't bound work, / and shipped a short-term embargo fix while we built it. / By design, **~99% less metadata work per request**.

---

## Backup · S1 · Versioned-object metrics for Uber: owning a customer feature end to end

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
