# 03 — STAR Stories (Phase 4 · draft v2 · 2026-11-01)

> 12 stories, written in first person. Each one traces to your files or to something you told me.
> **No invented numbers or events.** Where you don't have a measured result, the story uses what *was* measured (experiments, design arithmetic) plus an honest line. *Upgrade if true* and `[From memory]` mark spots that get stronger if you remember the answer. Skip them if you don't; every story works without them.

**Evidence legend**
- 🟢 from your files or your direct answers
- 🔵 arithmetic on numbers in your files: say "by design" or "roughly", and be ready to show the math
- 🟡 you asserted it, but the files are silent or credit someone else (see that story's weak spots)
- `[From memory]` / `[From memory]` / *Upgrade if true*: only you can answer. Leave it out of the spoken version unless you're sure

**How to use**
- Learn the **60-second version** cold. Use the 2.5–3 min script when the interviewer says "tell me more", or in a Bar Raiser round.
- In one loop, don't tell two stories from the same project (S1/S5, S2/S8, S3/S6) unless asked for "another example from that project".
- Every story ends on a number or a learning. Never end on "and the team was happy".

## Index

| # | Story | Hook (one line) | Primary LP / Google attribute | Required category | Status |
|---|---|---|---|---|---|
| S1 | Versioned-object metrics for Uber | Critical customer moving to OCI couldn't see versioned-object metrics; I shipped them in 8 weeks with zero write-path change | Ownership · Deliver Results / User first | — | 🟢 |
| S2 | Index Shrink | Index rebuilds caused 10 auto-cuts + 11 Sev2s and were paused in the two biggest regions; I built the safe alternative | Insist on Highest Standards · Invent & Simplify / Doing the right thing | **Reliability / data integrity** | 🟢 zero Sev2s from shrink |
| S3 | Paginated GET | One tenant drove 2.6 M chunk-row reads/s and ~30% 503s; I capped per-call metadata work at 100 chunks | Customer Obsession · Think Big / User first | Reliability (multi-tenant) | 🟢 |
| S4 | DBMS_LOCK Sev2 | Abort failed on every retry; I proved the hash collision, argued for convert, wrote the regression test | Dive Deep (backup) / Ambiguity | Data integrity (backup) | 🟢 your parts · "we shipped" |
| S5 | Disagreeing with the DBPerf expert on batch size | I asked DBPerf for input; their expert said 35–70, and I kept 15 on the data | Have Backbone · Are Right A Lot / Collaboration | **Conflict #1** | 🟢 |
| S6 | Re-enabling maintenance where managers had paused it | Managers had paused maintenance in IAD/PHX; I pushed to enable shrink there with data and controls | Have Backbone · Earn Trust / Challenge status quo, Leading without authority | **Conflict #2** | 🟢 |
| S7 | My Java 17 upgrade caused a perf regression | My upgrade passed tests, then perf2 regressed; about 8 weeks to pin it on a TLS default | Ownership · Learn & Be Curious / Growth mindset | **Failure #1** | 🟢 release slipped |
| S8 | My first Index Shrink rule was wrong | I chose by partition size; my own experiment showed same-size partitions needed opposite treatment | Are Right A Lot / Intellectual humility | **Failure #2** (small) | 🟢 |
| S9 | Per-shard rate limiting + my mentee's promotion | I designed OLM's adaptive per-shard limiter; my SD1 mentee built it; I reviewed with questions; they made SD2 | Hire & Develop · Earth's Best Employer / Leading without authority | **Mentoring** | 🟢 (design: you said) |
| S10 | SQL Server on Windows Storage Spaces (Nutanix) | Disks couldn't grow in place without risking DB consistency, so I designed growth by adding balanced disk sets | Customer Obsession · Invent & Simplify / Ambiguity | Durability (storage) | 🟢 needs outcome |
| S11 | SQL Server test automation + training (Nutanix) | ~80–90 automated functional tests, plus training sessions the team relied on | Insist on Highest Standards · Hire & Develop / Collaboration | Mentoring (backup) | 🟢 needs impact |
| S12 | Least-privilege Active Directory (Nutanix) | Object-level rights instead of OU-wide full control for AG listeners | Success & Scale Bring Broad Responsibility · Earn Trust / Doing the right thing | — | 🟢 needs customers |
| S13 | "Your design won't extend" (Nutanix) | Senior engineers said my Storage Spaces design wouldn't extend to Dynamic Disks; I changed how I design and built restore as standalone flow + AG orchestrator | Earn Trust · Learn & Be Curious / Growth mindset | **Feedback received (G2)** | 🟢 Dynamic Disks payoff confirmed · needs your first reaction |
| S14 | Explaining the 8-week trade-off to our TPM | Running tally at every checkout vs counting once a day: got the TPM behind query-time aggregation | Earn Trust · Customer Obsession / Communication | **Explain to non-technical (G11)** | 🟡 needs how you checked understanding + the support you got |
| S15 | "Nothing changed, so why is it slow?" | Explained to our TPM that paused index maintenance, not code, slowed a customer's queries | Earn Trust · Dive Deep / Communication | G11 backup | 🟡 outcome confirmed · needs the TPM's part |
| S16 | SQL Server snapshot in VSS's 10-second window (Nutanix) | Windows holds every write for at most 10 s while the storage snapshot commits; I optimised Era's snapshot path to fit inside it | Dive Deep · Insist on the Highest Standards / Technical depth | Hard technical problem (Nutanix) | 🟡 skeleton · needs what broke, what you changed, result |
| S17 | Soft Delete in OLM | Deletes became recoverable; the OLM purge, the one irreversible step, was built so nothing could make it happen early | Customer Obsession · Insist on the Highest Standards / User first, data integrity | Data integrity (Google) | 🟡 ownership + ship status unconfirmed |

**Ownership notes:**
- **OLM per-shard rate limiting** is now inside **S9**, told as "I designed it, my mentee built it" (git: CASPER-48918/48919 by your mentee; design by you, per your answer). Update the resume verb to match.
- **OLM Soft Delete** is now **S17**, drafted from the design docs (2026-11-04). Your role and whether it shipped are still unconfirmed: the docs name no author, and as of Dec 2025 they show the OLM tasks as not started.

**Set check:** failures S7, S8 ✔ · conflicts S5, S6 ✔ · mentoring S9 (+S11) ✔ · reliability/durability/data integrity S2 (+S3, S4, S10) ✔

---

## S1 · Versioned-object metrics for Uber: owning a customer feature end to end

**Hook:** Uber, a critical customer moving onto OCI, had no way to see metrics for their versioned objects. I had **8 weeks** to design, build, test and ship two new public metrics for their ~700 buckets, and I did it without touching the object write path.

| | |
|---|---|
| **Amazon LPs** | Primary: **Ownership**, **Deliver Results** · Secondary: Customer Obsession, Frugality, Insist on the Highest Standards, Dive Deep |
| **Google attributes** | Putting the user first · Bias to action · Doing the right thing (never publish a wrong number) |
| **Tilt** | Both ★★★. **Amazon:** this is a metrics pipeline over sharded data, close to Spektr's world; stress ownership and delivery. **Google:** stress correctness (fail closed) and the trade-off write-up. |

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

### Likely follow-ups
1. **Why not the summary table? Isn't that the scalable answer?** Yes, at scale. But it means a write-path change on the hottest path in the system, for one customer's ask. Query-time aggregation met the need with zero write-path risk. I documented the scale point: at ~10K buckets on one shard a run takes ~22 min. The design names the pre-aggregated table as the path "if broader adoption requires it", and we monitor query latency.
2. **What happens if a shard is down during a run?** That bucket is skipped for the cycle, not published as zero or partial. The coverage alarm fires below 95%. A missing point is honest; a wrong point is a customer billing question.
3. **The DBPerf expert suggested bigger batches. Why 15?** → S5. Cold runs on the skewed shard took 69 s vs 2 s warm. Bigger batches make the worst case worse, and a daily job doesn't need the throughput.
4. **DBPerf showed a full scan was faster. Why did you keep the index hint?** The full-scan result was for multi-bucket aggregation at large cardinality. With batches of 15 the access is selective, and the index plan was already optimal there. The 69 s cold run was data skew, not the plan.
5. **How does it scale to 10K buckets?** 🔵 Evenly spread across 10 shard workers: ~67 batches per shard × 2 s ≈ 2–3 min. Worst case, all on one heavy shard: ~22 min warm. Both fit a daily job. Beyond that, move to the summary table.
6. **How did you validate the numbers were right?** Unit tests for partial failure, timeouts and blackout, plus an end-to-end OST. [From memory: did you compare against a direct count on test buckets, or on Uber buckets before launch?]
7. **Why a separate service instead of extending the existing publisher?** Isolation. A slow aggregation job must never delay the metrics every other customer already depends on. It costs some duplicated publishing code, a trade-off I accepted.
8. **What did you delegate, and how?** → S9. I owned the design and the risky parts (query, fail-closed logic). Juniors took scoped implementation and test tasks.
9. **"What if you'd made the wrong architectural call?"** Two ways to be wrong, and they weren't symmetric. 🟢 (HLD appendix: pros/cons of each option)
   - **Summary table, if wrong:** changes across write/delete/versioning flows ("tight coupling with critical data path"), a backfill plus extensive validation, and the slower option against an 8-week deadline. A bug hits every customer's writes. A counting bug drifts silently instead of failing loudly. 🔵 (reasoning)
   - **Query-time, if wrong** (adoption outgrows it): bounded by design. Daily job in its own service (existing telemetry untouched), configured tenants only, one query per shard at a time, a feature flag to turn it off (it needs a deploy/restart, so **don't say "no deploy"**), fail closed, and a 95% coverage alarm. Worst case: a late or missing point, never a wrong one, and nothing on the write path.
   - **If pressed on the worst case:** 10K buckets all on one heavy shard, every batch cold → ~12.8 h, one query at a time at PARALLEL 2, still inside 24 h. Warm ≈ 22 min, the documented scale point.
   - **Close:** *"Being wrong one way risked every customer's writes. Being wrong the other way risked a late daily metric. That asymmetry was the decision."*
10. **"How did you communicate the decision and its uncertainty before committing?"** All in the HLD (M0, 27 Mar–3 Apr 2026), then design sign-off `[NEED: the reviewer's role]`: 🟢
   - **Options side by side**, including the two you didn't pick (summary table; extending the existing publisher), each with pros and cons.
   - **The trade-off stated outright:** "Accept trade-offs of higher query cost for faster implementation"; the pre-aggregated model "if broader adoption requires it".
   - **Ranges, not a single number:** warm / cold / pessimistic, for ~700 buckets (1.6 min / 2.7 min / 54 min) and for 10K (22 min / 23 min / 12.8 h on one shard; 2–3 min spread over 10 shards).
   - **Open questions named, then closed before commit:** the "Open Questions for DBperf" list → DBPERF-15959 → discussion summary → decisions marked "for now", plus "Monitor: query latency".
   - **Schedule risk surfaced:** milestone plan M0–M7 with owners and dates. You flagged that your on-call week overlapped the build and arranged a partial swap with a teammate. The T2 whitelisting thread and TEL-23840 started in week one.
11. **"What concrete metrics or outcomes did you see after launch? Surprises?"** No post-launch numbers in the files, but **two real production challenges** (your answer of 2026-11-02): 🟢
   - **Challenge 1: ORA-01489 from LISTAGG.** The tenant-DB query that builds each shard's bucket list used `LISTAGG`, which concatenates into one string capped at **4,000 bytes** (standard `MAX_STRING_SIZE`). Test tenants had a handful of buckets. In production, a shard with the customer's buckets overflowed it. Missed in test because **functional tests prove logic, not limits**.
     - Fix: `[NEED: what you actually did]`. The right fix is **one row per (shard, bucket), grouped in the service**, which matches the HLD's sequence diagram. If asked about alternatives: `ON OVERFLOW TRUNCATE` silently drops buckets (no); XMLAGG/CLOB works but is clunky; `MAX_STRING_SIZE=EXTENDED` is DB-wide and still finite.
     - `[Confirm: how it surfaced. If the tenant lookup failing just meant missing metrics, say "because it failed closed, it showed up as missing metrics, not wrong ones".]`
     - Credit: a teammate built the tenant-DB mapping piece (HLD M2). Say "we hit", and "I fixed" only if you did.
   - **Challenge 2: slow queries on fragmented IAD/PHX shards.** Index rebuilds had been paused there for a couple of months, so the version-table indexes were heavily fragmented. You investigated with DBPerf and did a **manual index rebuild**. `[Upgrade if remembered: before/after query time]`
     - **Cross-project link (true, and strong):** paused maintenance in IAD/PHX is exactly the problem Index Shrink (S2) was built to fix.
     - **The insight that challenged the bet:** *query-time aggregation is only as fast as the indexes it scans.* A pre-aggregated table wouldn't care. Healthy index maintenance became an explicit dependency of this feature.
     - **"Why not use your own shrink?"** `[NEED: the real reason. Options: (a) those partitions were past the 300 bytesPerRow line, where your own rule sends them to rebuild because shrink is far less effective there; (b) shrink wasn't enabled on those shards yet, since it went on a subset of shards first.]` **Don't say shrink fixed it** unless it did.
   - **Pre-launch findings still worth one line:** cost was data skew (69 s cold vs 2 s warm), and GROUP BY batching gave ~8× throughput.
   - **Careful:** the ORR export (30 Jun 2026) still shows alarm deployment as "TO DO". Don't claim the alarms were live at launch unless you know.
   - **Close:** *"Both surprises taught me the same thing: the risks in a read-heavy design sit in what it reads. Limits in the lookup, health of the indexes."*
12. **"Knowing what you know now, what would you do differently?"** Same decision, three changes:
   - **Same call:** both surprises were fixed without touching the write path `[and, if confirmed, neither produced a wrong number]`, so the asymmetry held.
   - **Test limits, not just logic:** a test with hundreds of buckets on one shard (past LISTAGG's 4,000 bytes), or a read-only dry run against the real tenant before launch. Design rule: never pack an unbounded list into one value; return rows.
   - **Make index health an explicit dependency:** check fragmentation on the target shards before launch, and put Index Shrink's existing `bytes.per.row` metric next to query latency on this feature's dashboard. 🟢 (metric is in the Index Shrink design)
   - **Write the read-path risks down:** the versioned-metrics ORR literally says **"Risks: N/A"**. Today: unbounded lookups, index health where maintenance is paused, cold-cache skew. 🟢 (ORR p.4)
   - **Close:** *"The bet was right. My picture of what it depended on was too narrow."*

### Weak spots & risks
- Uber's reaction is qualitative ("happy; finally have visibility"). That's enough. Don't inflate it into numbers.
- It can sound like "one feature". Lead with the **decisions** (write path vs query time, fail closed) and the **cross-team** piece.
- **No formal "22-minute trigger".** The HLD gives the 10K estimates, names the pre-aggregated model "if broader adoption requires it", and lists "Monitor: query latency". Say **"documented scale point"**. Don't say "I set a 22-minute SLA/alarm", because there isn't a runtime alarm on record.
- Have the DBPerf back-and-forth (index vs full scan) straight. It's a likely Dive Deep probe.

**Sources:** `Uber Metrics/High Level Design for metrics to…pdf`, `Uber Metrics/Operational readiness review for…pdf`, `Uber Metrics/Versioned Object Operational Rea…pdf`, `Uber Metrics/20709909603_…pdf` (milestones), `Shivang_Badola_Resume.pdf`

---

## S2 · Index Shrink: making database maintenance safe enough to turn back on

**Hook:** Index rebuilds on our metadata databases had caused **10 auto-cuts and 11 Sev2s** in 2–3 months and were paused in our two biggest regions. I designed an in-place alternative, proved it with production experiments, and rolled it out shard by shard, big regions last.

| | |
|---|---|
| **Amazon LPs** | Primary: **Insist on the Highest Standards**, **Invent and Simplify** · Secondary: Dive Deep, Ownership, Success & Scale Bring Broad Responsibility, Frugality |
| **Google attributes** | **Doing the right thing** (data integrity) · Comfort with ambiguity · Data-driven decisions |
| **Tilt** | Both ★★★. **Google:** storage durability and availability; lead with the corruption failsafe and the no-data-loss guarantee. **Amazon:** lead with the incident counts, experiments and phased rollout (operational excellence). |

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

### Likely follow-ups
1. **Why not just run rebuilds off-peak?** Timing doesn't change what a rebuild needs: TEMP, 2× space, journal tables. Our most constrained regions were exactly where rebuilds were already paused. The problem was the shape of the operation, not when it ran.
2. **What does shrink do, and does it lock?** COMPACT moves rows online to fill blocks. The second step releases space with a brief lock. That's why it's capped at one operation per CDB, with a 14-day window.
3. **What if shrink corrupts data?** It can't lose data. On ORA-01578 it falls back to exactly one rebuild from table data. I tested it by inducing corruption with DBPerf, and a unit test enforces "exactly once".
4. **Why 300 / 50%?** A deviation from the ideal of 200. In the experiments, rebuild beat shrink only at heavy fragmentation (402 bytesPerRow: 11 vs 31 min). It's configurable per region.
5. **Rollback?** Global dry-run, or remove a shard from the allow-list. Both are JVM args, no deploy. The only Sev2 page is a failed kill of a stuck operation.
6. **Who resisted?** → S6. Managers had paused maintenance in IAD/PHX; I showed shrink didn't have the properties that caused the pause and gave them per-shard control.
7. **What's the result, then?** Zero Sev2s from shrink, maintenance running again in IAD/PHX, plus the experiment numbers. If pushed for a fleet-wide metric, give the honest line, then add: *"If I did it again, I'd capture a baseline before launch, so the result is measured, not remembered."*
8. **How is this different from the auto-rebuild work for OLM listing failures?** That was a colleague's project, rebuilding partitions to fix listing failures. Shrink is my lightweight alternative for the moderate-fragmentation case.
9. **"Did paused maintenance cost you anywhere else?"** Yes, on your own next project. The versioned-metrics queries (S1) ran slowly on IAD/PHX shards that were heavily fragmented after rebuilds had been paused for months. You investigated with DBPerf and did a manual rebuild. 🟢 (your answer of 2026-11-02) It shows why keeping maintenance running matters beyond incidents: every read-heavy feature inherits index health. Only say shrink was involved in that fix if it actually was.

### Weak spots & risks
- **No fleet-wide after-number**, but "zero Sev2s from shrink + maintenance back in IAD/PHX" is a real result. Answer 7 covers the follow-up.
- "10 auto-cuts + 11 Sev2s" were caused by **rebuilds**, before your work. Never imply shrink removed exactly those 21.
- Don't blur this with Auto Index Rebuild (not yours).

**Sources:**
- `Index Shrinks/Executive Summary of Index Shrin…pdf` (experiments)
- `Index Shrinks/Index Shrink Design Proposal_…pdf` (rule; reuse of the PriorityQueue)
- `Index Shrinks/Index Shrink Operational Readine…pdf` (problem, waves, rollback)
- `Index Shrinks/Index Rebuild_Shrink - Experiment .pdf`, `…first experiment.pdf`, `Functional Testing Summary_…pdf`
- your answers of 2026-10-31 and 2026-11-01

---

## S3 · Paginated GET: stopping one tenant's huge downloads from hurting everyone

**Hook:** One tenant's GETs on a single 281 GB object pushed **~2.6 million chunk-row reads per second** into a metadata shard and caused **~30% 503s**. I redesigned GET so every metadata call does bounded work, **at most 100 chunks**, which also made throttling meaningful.

| | |
|---|---|
| **Amazon LPs** | Primary: **Customer Obsession** (every tenant, not just the loud one), **Think Big** · Secondary: Dive Deep, Invent and Simplify, Bias for Action, Ownership |
| **Google attributes** | **Putting the user first** · Challenging the status quo · Multi-tenant reliability |
| **Tilt** | Both ★★★. **Google:** noisy-neighbour isolation, bounded work per request, and the consistency token. **Amazon:** an incident turned into a multi-pronged fix, with a short-term mitigation shipped while the long-term design was built. |

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

### Likely follow-ups
1. **Isn't this an abuse problem? Why not just throttle?** The design doc says it outright: the traffic pattern looked more like an attack. But you can't throttle fairly while one request can cost 10,000× another. So both: embargo rules and runbooks short term, and pagination so throttling is per unit of work. 🟢
2. **Doesn't 100 calls instead of 1 add DB load?** The total rows for one full download are the same, spread over the transfer instead of in one burst. It does add per-call overhead and throttling odds, which I called out in the design. 🟢
3. **What happens if MDS throttles mid-stream?** After a 200 has started, a 429 can't be returned, so the Web Server drops the connection. That's why the design notes it and the public docs needed updating. 🟢
4. **Read timeouts during page fetches?** Prefetching the next page while the current one streams. Scoped as an incremental optimisation after v1. 🟢
5. **How did you pick 100?** It was the starting value, calibrated by testing query latency against page size, and it's configurable. 🟢 (your answer + doc)
6. **Why the POC?** Hopping between the event loop and worker threads many times per request didn't exist anywhere in the codebase. I wanted proof it was safe before building the core data path on it. 🟢
7. **Why the etag in the token?** Consistency. Without it, an overwrite mid-download could stitch chunks from two versions into one response, which is silent corruption.
8. **Why not byte ranges?** MDS work per call would depend on the customer's part sizes. Chunk count is fixed by construction.

### Disagreement variant (use **only if** a teammate really argued for byte ranges)
Your other chat's version ("a senior teammate proposed byte-range… they reviewed my LLD") turns this into a conflict story. **The design doc supports the arguments** (code reuse, no MDS changes, range-read work in progress), **but not who made them.** If a real person pushed for it, tell it that way and name their valid point (speed). If not, keep it as a design trade-off. You already have two real conflicts (S5, S6).

### Weak spots & risks
- "99%" is a **design** property, so say "by design". If asked "did incidents stop?", answer only from what you know.
- **About a year from incident (Mar 2025) to ship (around Mar–Apr 2026).** Expect "why so long?". Answer: it's the core data path, so it went behind a feature flag with scale and perf testing, and the short-term embargo + runbook mitigation covered the gap. *(Confirm the year. I assumed 2026 because your LLD is from July 2025.)*
- If asked about client disconnects or backpressure: the doc doesn't cover them, so answer from memory or say what you'd do.

**Sources:**
- `Pagination GetObjectAPI/MDS Paginaton for GET object_…pdf`: background (three NOCs), throttling example, POC note ("I was able to write simple independent test code…"), prefetch and timeouts, page-size calibration, feature flag, short-term remediation, rejected proposal
- `Pagination GetObjectAPI/Low Level Design for MDS Paginat_…pdf`, `Pagination GetObjectAPI/WS GET Paginated_…pdf`
- `Shivang_Badola_Resume.pdf`
- your answers of 2026-10-31 and 2026-11-01

---

## S4 · DBMS_LOCK Sev2: proving a hash collision and locking it down

**Hook:** An internal customer's cluster deletions were blocked because aborting one multipart upload failed on **every** retry. I proved, with a hash POC, that two unrelated lock keys landed on the same Oracle lock ID. I argued for the targeted fix we shipped as a patch, and wrote the regression test that pins the exact collision.

| | |
|---|---|
| **Amazon LPs** | Primary: **Dive Deep** · Secondary: Are Right A Lot (the trade-off), Insist on the Highest Standards (the test), Bias for Action (patch now, redesign later) |
| **Google attributes** | Comfort with ambiguity · Data-driven debugging · Collaboration (name teammates accurately) |
| **Tilt** | **Google ★★★** (deep technical reasoning plus accurate credit) · **Amazon ★★** (use as a Dive Deep *backup*; ownership probes will come) |

> **What's yours and what's the team's.** Keep this exact, because it's the line a Bar Raiser will test.
> - 🟢 **Yours (your answers of 2026-11-01/02):** you were **on-call when the ticket came in**, and **didn't just hand it over: you kept working the root cause on your own initiative**; you worked the Sev2; you ran the **ORA_HASH POC** in the test env proving the collision; you **wrote the regression test** (`testExclusiveAfterSharedLockHashCollision`); you **argued for convert** over separate ID ranges.
> - 🟢 **Team (ticket):** a teammate (Jie) first spotted that two locks were conflicting and showed the lock looked free when called by hand. Another teammate (Himanshu) wrote up the RCA and **raised the fix PR** (merged 16 Jul 2025). A senior engineer endorsed the convert approach.
> - **In the script, say "we shipped".** If asked "who wrote the PR?": *"My teammate raised it. I did the hash proof and wrote the regression test, and I'd pushed for the convert approach."* That's honest, and it still shows you at senior level.

### Situation & Task (~20%)
- **Sev2, São Paulo (GRU), 24 Apr – 18 Jun 2025.** 🟢
- **OKE** (Oracle's Kubernetes service) couldn't abort an uncommitted multipart upload in its etcd-backups bucket. Its cluster-deletion workflow was **blocked**. 🟢
- Every retry failed with `ORA-20999: unable to acquire dbms_lock in x_mode … with code 4`. 🟢
- The confusing part: logs showed **no other operations on the bucket**, and calling the lock procedure by hand worked. The first theory was conflicting operations on the customer side. 🟢
- MDS had recently moved the uploads path onto Oracle **DBMS_LOCK**. 🟢
- **My task:** it came in on **my on-call week**, so it landed with me first. On-call meant triage and getting the customer unblocked. I went further: prove what was really happening, help pick the fix, and make sure it could never silently come back. 🟢 (your answers)

### Action (~60%)
1. **Treated the 100% failure rate as the clue.** Under no load, a lock that fails *every* time isn't contention; it's **deterministic**. So I went to the lock code. 🟢
2. **Read the lock path.** 🟢 (`CasperTransaction.sql`, `Locks.sql`)
   - `AbortUpload` first takes a **shared** lock for bucket migration, keyed `'BM' || bucketId`.
   - Then it takes an **exclusive** lock keyed `'PUT' || uploadId`.
   - Both keys become lock IDs through `ORA_HASH(key, 1073741823)`: **one shared space of ~1.07 billion IDs**.
3. **Proved it with a hash POC** in our test environment. 🟢 (your answer; repro shows bucket `4a480ce5…` + upload `73a069f8…`)
   - I hashed the two real keys from the ticket, and **they landed on the same lock ID**.
   - DBMS_LOCK's return code **4** means "this session already owns this lock". The session held that ID in shared mode from the first step, so the exclusive request could **never** succeed.
   - It also explained the phantom: a manual call runs in a fresh session that doesn't hold the BM lock, so it "works".
4. **Made the case for the fix.** 🟢 (your answer) The two options from the RCA:
   - **(a) Separate ID ranges** for each lock type.
     - Removes collisions *between* lock types by construction.
     - But it touches **every caller** of the lock package.
     - It's unsafe mid-rollout: during a rolling deploy, an old host and a new host compute **different IDs for the same key**, so they don't exclude each other. That's a correctness hole, unless you run a dual-locking phase across releases.
     - `ALLOCATE_UNIQUE`'s range leaves room for only one more space; the RCA flagged the problem of a third lock type.
   - **(b) Catch code 4 and `DBMS_LOCK.CONVERT` shared → exclusive.**
     - Fixes exactly the failure customers hit (same session, colliding IDs).
     - One procedure plus one exception handler in the abort path.
     - **No ID migration**, so it's safe while old and new hosts run side by side.
     - Small enough to ship **as a patch**.
   - My argument: **(b) now, because time-to-fix matters for a live customer, and (a) is the right long-term design.** 🟢 (your words: "time wise our approach is better, long term is ranges one")
5. **Made sure it can't come back silently.** 🟢 (your answer; test file)
   - I wrote a deterministic regression test (`testExclusiveAfterSharedLockHashCollision`) using the **real colliding bucket/upload pair**: begin both uploads, abort both, assert both are gone.
   - It fails without the fix and passes with it. It can't pass by luck.
6. **Shipped.** During the Sev2, the team mitigated by moving the uploads path off DBMS_LOCK. **We** then rolled out the convert fix **as a patch** to the July release. 🟢

### Result + learning
- 🟢 The customer was unblocked (mitigation; Sev2 resolved 18 Jun). The permanent fix went out **as a patch in July 2025**, with a regression test pinned to the exact collision.
- 🔵 **Two kinds of collision. Keep them separate.**
  - **Same session (what the customer hit → permanent failure):** a bucket's `BM` key and its upload's `PUT` key collide. That's **1 in 2³⁰ ≈ 1 in 1.07 B per abort**, so the expected count = aborts ÷ 1.07 B. After **~744 M cumulative aborts** it's more likely than not to have happened at least once (95% by ~3.2 B). Rare per abort, certain at fleet scale over time, and permanent when it hits.
  - **Cross-session (transient false contention):** two unrelated keys held **at the same moment** share an ID. This is where the birthday bound applies: **~38.6 K locks held at once** gives ~50% that some pair collides. The cost is a ≤1 s wait and a retry. Convert doesn't fix this, and doesn't need to.
  - **Don't** use the birthday bound to argue for the permanent failure. A sharp interviewer will catch it.
- **Learning:** when something fails **100%** of the time under no load, stop looking for contention and look for determinism. And whenever several kinds of keys share one hashed ID space, ask what happens when two of *your own* keys collide.

### Spoken script (2.5–3 min)
> We had a Sev2 in our São Paulo region. / OKE, Oracle's Kubernetes service, couldn't abort a multipart upload, / which blocked their cluster deletions. / Every retry failed with "unable to acquire lock". / But the logs showed **nothing else touching the bucket**, / and a teammate had shown the lock looked free when you called it by hand. / The first theory was that the customer was running conflicting operations.
>
> What caught my attention was the failure rate. / It wasn't failing sometimes; it failed **every single time**. / Under no load, that's not contention. That's **deterministic**. / So I went to the lock code.
>
> Abort takes two locks: / a shared lock for bucket migration, keyed on the bucket, / then an exclusive lock keyed on the upload. / Both keys get hashed into **one space of about a billion lock IDs**. / So I ran a POC in our test environment / with the exact bucket and upload IDs from the ticket, / and **they hashed to the same lock ID**. / Oracle's error code 4 means "you already own this lock". / The session already held it in shared mode, / so asking for exclusive could **never** succeed. / And that explained the phantom: / a manual call runs in a fresh session, so there's nothing to collide with.
>
> There were two ways to fix it. / The clean long-term option was separate ID ranges per lock type. / But that touches every caller, / and during a rolling deploy, old and new hosts compute different IDs for the same key, / so for a while they wouldn't protect each other. / The other was to catch that specific error and **convert** the lock we already hold to exclusive: / one path, no migration, safe to roll out. / I argued for **convert now, as a patch**, / because a customer was blocked, / with separate ranges as the right long-term design.
>
> Then I wanted to make sure it could never come back silently. / I wrote a **deterministic regression test** with the real colliding pair from production. / It fails without the fix, passes with it, and can't pass by luck.
>
> We rolled the fix out as a patch in the July release. / Per abort it's a one-in-a-billion event, / but across a fleet, "rare" is "inevitable".
>
> What I took away: / when something fails a hundred percent of the time, stop thinking about load. / And whenever you hash different kinds of keys into one space, / ask what happens when two of your own keys collide.

### 60-second version
> In a Sev2, an internal customer couldn't abort a multipart upload, which blocked their cluster deletions, / and every retry failed on a lock even though nothing else touched the bucket. / **100% failure under no load** told me it was deterministic, not contention. / I ran a hash POC with the real IDs: / the bucket-migration lock and the upload lock **hashed to the same Oracle lock ID**, / so the session was asking for a lock it already held. / I argued for a targeted fix, **converting the held lock**, shipped as a patch, / over the cleaner but riskier separate ID ranges, which I'd keep as the long-term design. / And I wrote a deterministic regression test with the real colliding pair, so it can't come back silently.

### Likely follow-ups
1. **What exactly was your role?** I worked the Sev2, proved the collision with a hash POC, wrote the regression test, and pushed for the convert approach. A teammate first spotted the conflict, and another raised the PR. *(Say it like this, plainly.)*
   - **"Was it assigned to you, or did you self-select?"** *"Both, really. It came in on my on-call week, so it landed with me first. I could have triaged it and handed it over at the end of my week, and the working theory even pointed at the customer's side. But a customer was blocked, and a lock failing every single time under no load didn't make sense to me. It was too interesting a problem to let go. So I didn't just hand it over. I kept working the root cause alongside my regular work: the hash POC, the case for convert, and the regression test. A teammate took over the ticket and raised the fix PR."* Then give your role on the team, with your **exact title**. 🟢 (your answers of 2026-11-02)
2. **Why convert instead of separate ranges?**
   - Convert fixes the exact customer-visible failure with one targeted change, needs no ID migration, and is safe during a rolling deploy, so it could go out as a patch.
   - Separate ranges is cleaner, but it touches every caller and needs a dual-locking transition. Otherwise old and new hosts compute different IDs for the same key and don't exclude each other.
3. **What does convert *not* fix?** Collisions across **different** sessions. If session A holds the colliding ID for an unrelated key, session B waits up to the 1-second timeout and fails, then succeeds on retry. That's **transient false contention**, rare and retryable. Convert fixes the **permanent** same-session failure, which is what customers hit. *(This answer shows real depth.)*
4. **Any side effect of converting?** For that one transaction, the abort holds the colliding ID exclusively, briefly blocking anything else that needs it. A rare, short serialization instead of a guaranteed failure.
5. **Why not `ALLOCATE_UNIQUE`?** It maps names to unique IDs, so there are no collisions. But it keeps a row per name (millions of upload IDs), and Oracle documents that it **performs a COMMIT**, which you can't do in the middle of an abort transaction. *(Check the Oracle docs before quoting the COMMIT detail.)*
6. **How likely is a collision?** The permanent kind: **1 in 1.07 B per abort**, so expected failures = aborts ÷ 1.07 B, and ~50% that at least one has happened after ~744 M cumulative aborts. The transient cross-session kind follows the birthday bound: ~38.6 K locks held at once gives ~50% that some pair collides, at the cost of a short wait and a retry.
   - **"What was the measurable impact?"** Customer: ticket opened 24 Apr 2025; the team had root cause by ~3 May; Sev2 resolved 18 Jun by the config mitigation (uploads off DBMS_LOCK); permanent fix in the July patch. `[NEED: when the customer was actually unblocked, and why closure took until 18 Jun]`. Fleet: no fleet-wide count; this is the only occurrence you know of `[confirm]`. Give the math above. The fix turned the customer-visible failure from **permanent** into **at worst a brief wait**. The patch also gave the code-4 case its own error code, so occurrences can be counted from now on.
7. **How did you make sure it won't regress?** A deterministic IT with the real colliding pair from production. Random keys would almost never collide, so only the real pair proves the fix.
8. **What would you do long term?** Separate ID spaces per lock type by design, rolled out with a dual-locking phase, plus a test that forces a cross-type collision.
9. **"Walk me through the steps you personally took. What if you hadn't pursued it?"** Four steps, all yours: 🟢
   - **Read the pattern:** 100% failure, no load, manual call works → deterministic, and tied to state this session has that a fresh one doesn't.
   - **Read the abort path:** shared `'BM'||bucketId`, then exclusive `'PUT'||uploadId`, both through `ORA_HASH(…, 1073741823)` → can two of our own keys collide?
   - **Hash POC** in the test env with the real IDs → same lock ID; code 4 = "already own it" explains every retry failing and the phantom.
   - **Made it reproducible:** the real-pair test fails every time without a fix, and it became the regression test.
   - **Counterfactual:** stopping at the first theory points the customer at a problem they didn't have. The mitigation (uploads off DBMS_LOCK) only hides it: switching back brings permanent failures back: 1 in 1.07 B per abort, so ~50% that at least one has happened after ~744 M cumulative aborts, and every one is permanent. Without the real-pair test, nothing catches a regression, because random keys essentially never collide.
   - **Don't claim:** the log search or the manual lock test (a teammate's), the RCA write-up, or the PR.
10. **"Beyond the technical insight, what did this change about how you work?"** Two changes, each with a later example:
   - **A mitigation isn't the finish line.** Done = cause proven + fix targets it + a test that fails without it. *Applied:* Index Shrink, later in 2025. You induced index-block corruption on purpose with a database SME to see real behaviour, then pinned "exactly one rebuild" with a deterministic unit test. 🟢 (design doc, ORR)
   - **When evidence contradicts the working theory, chase the evidence**, especially when the theory blames the customer. *Applied:* Apr 2026, versioned metrics. The DBPerf expert's rule of thumb said 35–70 per batch, your measurement said cold batches take 69 s, so you kept 15 (S5, one line only). 🟢
   - Close: *"I own the outcome, not the ticket, and I'm not done until a test says so."* Only say lessons you actually feel.

### Weak spots & risks
- **The PR isn't yours on record.** Never say "I wrote the fix" or "I raised the PR". "We shipped", plus the follow-up 1 answer, is safe and still strong.
- Timeline accuracy: the Sev2 was resolved by the mitigation (18 Jun). The convert fix came after, as a July patch. Don't imply the patch closed the Sev2.
- **You were on-call**, so triage was officially yours. The root cause **after** handover wasn't, and you kept going on your own initiative. That makes S4 a **usable but partial** answer to "a problem outside your responsibility". Make the boundary explicit: *"triage was mine; the root cause after my week wasn't."* A story where it was never yours at all would still be cleaner (gap G8).
- Lead with **"a customer was blocked"**, then **"too interesting to let go"**. Curiosity alone can sound like chasing fun problems. Customer impact first reads as Ownership.

**Sources:**
- `DBMS Hash Collision/DBMS_HASH_Collision_ticket/`:
  - `parent_issue_ticket_screen_shot_1.0/2.0.png` (Sev2, impact, timeline)
  - `RCA_from_Jie_IC5_in_parent_ticket.png`
  - `Screenshot 2025-08-13….png` (RCA, PR, merge, July patch; senior endorsement)
  - `PR commit screen shot.png`, `repro_2.0.png`
  - `RCA.txt`, `Locks.sql`, `CasperTransaction.sql`, `testExclusiveAfterSharedLockHashCollision.java`, `log_stack_trace.txt`
- Your answers of 2026-11-01 (Sev2 involvement, hash POC, regression test, argued for convert, patch rollout)

---

## S5 · Disagreeing with the DBPerf expert on batch size (conflict #1)

**Hook:** I asked our database-performance team how big my query batches should be. Their expert recommended **3–5× bigger** than mine. I kept 15 because of what our cold-run data showed, and we wrote down what would change the decision.

| | |
|---|---|
| **Amazon LPs** | Primary: **Have Backbone; Disagree and Commit**, **Are Right A Lot** · Secondary: Dive Deep, Earn Trust |
| **Google attributes** | **Collaboration** · Intellectual humility (you asked for the expert's input first) · Data-driven decisions |
| **Tilt** | **Google ★★★**: a respectful, data-driven disagreement with an expert you invited in. **Amazon ★★**: modest stakes, so use it for "disagreed with an expert / someone more senior". S6 is the bigger conflict. |

### Situation & Task (~20%)
- In the Uber metrics job (S1), each shard worker runs GROUP BY queries over **batches of bucket IDs**. I was using **15 per batch**. 🟢
- I **asked DBPerf for input**: I opened **DBPERF-15959** with open questions on the parallelism factor, GROUP BY vs per-bucket fan-out, and index choices. 🟢
- In that review, **Mihaela Juganaru** (DB-performance SME) recommended **5–10% of total buckets** per batch, which for ~700 buckets is **35–70**. That's where we disagreed. 🟢 (your answer: "we had a disagreement")
- She's the expert on DB load. I owned the feature and its on-call. **Task:** make the right call without dismissing the expertise I'd asked for.

### Action (~60%)
1. **I brought data, not an opinion.** On the heaviest shard (126), the **first cold run of a batch took ~69 s**; warm runs took ~2 s. Testing with DBPerf had already shown that query-plan changes moved latency by fractions of a second. The real bottleneck was **data skew**. 🟢
2. **I showed the trade-off in numbers.** 🔵
   - On a skewed shard, a bigger batch makes each query heavier on exactly the shard that's already the hot spot. **The worst case gets worse.**
   - The job runs **once every 24 hours**. At 15, Uber's heaviest shard finishes in **~1.5 min warm, ~2.7 min cold-ish** (47 batches).
   - Going to 50 saves roughly a minute a day, and the price is a much larger single query on the hottest shard.
3. **I didn't dismiss her rule.** I argued that this workload was the **exception**: heavy skew, plus a daily schedule where throughput barely matters. 🟢
4. **We recorded the decision and how to revisit it.** The design records "**continue with 15 for now**: safer under skewed load, prevents DB overloading", with action items to proceed with the index-based query, **retain batch size 15**, and **monitor query latency**. 🟢

### Result + learning
- 🟢 Decision documented with its reasoning and a monitoring action item. "For now" was explicit, so latency data could reopen it.
- 🟢 The job shipped at 15 in MDS 6.5 (S1).
- *Upgrade if true:* "and it never set off a DB alarm."
- **Learning:** when you disagree with an expert you invited in, **argue from your own data**, treat their rule as the default you're asking an exception to, and agree on the metric that would change your mind.

### Spoken script (~2.5 min)
> On the Uber metrics project, / each shard worker ran aggregation queries over batches of bucket IDs, / and I was using fifteen per batch. / I wanted our database-performance team to check my approach, / so I opened a ticket with them and listed my open questions.
>
> Their expert came back with a rule of thumb: / five to ten percent of buckets per batch, / which for Uber meant **thirty-five to seventy**. / She knows Oracle performance far better than I do, / so I took it seriously, / but I didn't think it fit this workload.
>
> I'd measured that on Uber's heaviest shard, / the first, cold run of a batch took about **sixty-nine seconds**, / while warm runs took two. / And our own testing together had shown / that changing the query plan only moved latency by fractions of a second. / The problem was **data skew**.
>
> So I laid it out in numbers. / Bigger batches make every query heavier, / on exactly the shard that's already the hot spot, / so the worst case gets worse. / And the job runs **once a day**. / At fifteen, the heaviest shard finishes in two to three minutes. / Going to fifty saves about a minute a day, / and we pay for it with a much bigger query on the hottest shard.
>
> I framed it as an exception to her rule, not a rejection of it. / We wrote into the design: / keep fifteen **for now**, because it's safer under skew, / and **monitor query latency**, / so the data could reopen it.
>
> What I learned: / when you disagree with an expert you asked for help, / bring your own data, / treat their rule as the default you're asking an exception to, / and agree on what would change your mind.

### 60-second version
> I asked our DB-performance team to review my aggregation job. / Their expert recommended batches of **35 to 70** buckets; I was using **15**. / I'd measured that cold runs on our most skewed shard took **69 seconds** versus 2 warm, / so bigger batches would make the worst case worse on exactly that shard, / and since the job runs **once a day**, the gain was about a minute. / I framed it as an exception to her rule, not a rejection, / and we documented "keep 15 for now, **monitor query latency**", / so data could reopen the decision.

### Likely follow-ups
1. **What if she'd insisted?** She was the approver for DB load, so I'd have disagreed and committed: run at her number with a latency alarm, and keep the batch size easy to change back. *(Hypothetical. Phrase it as "I would".)*
2. **Wasn't this low-stakes?** Partly, which is why I handled it with data, not escalation. But the stakes were query load on a shard that serves every tenant on it.
3. **How did you know skew was the bottleneck?** Index vs full scan and PARALLEL 2 vs 4 moved latency by fractions of a second. Cold vs warm moved it by 35×.
4. **How do you build trust with an expert you disagree with?** Ask for their input early (I opened the ticket), take the rule seriously, argue the exception with data, and make the decision reversible.
5. **What did you learn from her?** The plan work: forcing a full scan dropped one test from ~8 s to ~2–2.5 s, and PARALLEL 4 gained only ~0.4 s over 2 for more resources, so I kept PARALLEL 2. 🟢
6. **Tell me about a bigger conflict.** → S6.

### Weak spots & risks
- Mild by Amazon standards. Don't use it as your "biggest conflict".
- Don't claim she "agreed". The file records the decision, not her sign-off. Say "we documented…".

**Sources:** `Uber Metrics/High Level Design for metrics to…pdf` ("Open Questions for DBperf", "Summary of Discussion with DBPerf", "Batch Size Strategy", "Back of the envelope calculations"; DBPERF-15959). Your answer of 2026-11-01.

---

## S6 · Pushing to turn maintenance back on in the regions managers had paused (conflict #2)

**Hook:** After rebuilds hurt our two biggest regions, managers had paused index maintenance there. I pushed to enable Index Shrink in exactly those regions, because the pause was the problem shrink was built to solve.

| | |
|---|---|
| **Amazon LPs** | Primary: **Have Backbone; Disagree and Commit**, **Earn Trust** · Secondary: Ownership, Dive Deep, Customer Obsession |
| **Google attributes** | **Challenging the status quo** · **Leading without authority** · Data-driven decisions |
| **Tilt** | Both ★★★. **Amazon:** backbone with data, plus giving leadership the controls. **Google:** respectfully challenging a "safe" default. |

### Situation & Task (~20%)
- Online index rebuilds had caused TEMP and filesystem spikes, redo spikes, journal-table cleanup failures and library-cache contention (503s), with **10 auto-cuts and 11 Sev2s** in 2–3 months. 🟢
- Managers had **paused or deferred rebuilds** in several regions, including **IAD and PHX**: our biggest, capacity-constrained regions, home to strategic workloads such as Stargate's onboarding. 🟢
- The pause was a reasonable call. But it meant index maintenance **wasn't happening at all** in the two regions with the most load. 🟢
- **Task:** Index Shrink was my project, and I believed IAD/PHX were its best use case. The default, after the pain, was to leave those regions alone. I had to get managers to agree to run maintenance there again. 🟢 (your answer)

### Action (~60%)
1. **I separated the operation from the pain.** What hurt IAD/PHX wasn't "maintenance". It was the **rebuild's resource profile**. I mapped each cause of the pause to what shrink does instead: 🟢 (ORR "key attractive features")
   - in place, so **no TEMP** and no filesystem growth
   - **no journal table**
   - redo **spread out**, not spiked
   - **no library-cache contention**, so no 503s
2. **I brought evidence, not assurances.** My experiment results, including production in EU-PARIS: 🟢
   - same duration as rebuild on moderate fragmentation, without the side effects
   - completed on a 63%-deleted partition where **rebuild failed outright**
3. **I treated their risk as a design input.** Every concern got a control they could use themselves: 🟢
   - a **per-shard allow-list**, so we could start with one or a few shards
   - a **global dry-run**
   - both are JVM args, so **rollback needs no deploy**
   - one operation per CDB at a time
   - the corruption failsafe
   - alarms deployed **before** enablement (17 Dec / 9 Jan)
4. **I let them watch it work before it touched IAD/PHX.** 🟢 (ORR plan)
   - The rollout put IAD and PHX in the **final wave**, after the small regions in December, CDG/DXB, the rest of the non-embargo regions, and SJC/ORD.
   - There too, it started with **one or a subset of shards**.

### Result + learning
- 🟢 **IAD and PHX were enabled** in the final wave (planned 30 Jan 2026), after it ran cleanly in the smaller regions. (your answer)
- 🟢 **No Sev2s from shrink**, there or anywhere else, through the rollout and the months after. (your answer)
- **Learning:** when someone has paused something for a good reason, **don't argue against their reason. Show how your proposal removes it**, and give them the controls to stop it.

### Spoken script (2.5–3 min)
> After index rebuilds had caused a string of incidents, / ten auto-cuts and eleven Sev2s in a couple of months, / our managers **paused index maintenance in IAD and PHX**, / our two biggest regions. / Honestly, that was a reasonable call. / But it meant maintenance just wasn't happening in the regions with the most load.
>
> I'd built Index Shrink as the lightweight alternative, / and I was convinced those two regions were its **perfect use case**. / So I asked to enable it there, / which meant asking managers to undo a pause they'd put in for good reasons.
>
> I didn't argue that the pause was wrong. / I argued that **the reasons for the pause didn't apply to shrink**. / What hurt those regions was how a rebuild uses resources: / temp space, double the disk, journal tables, redo spikes, / and contention that turned into 503s for customers. / Shrink runs in place, / no temp space, no journal table, / redo spread out instead of spiking.
>
> And I brought data, not promises. / I showed the experiments, including in production: / same time as a rebuild on moderate fragmentation, without the side effects, / and on one partition, the **rebuild failed outright while shrink finished**.
>
> Then I treated their risk as a design requirement. / A per-shard allow-list, so we start with one or two shards. / A global dry-run switch. / Both changeable **without a deploy**, so they could stop it in minutes. / Alarms in place before we enabled anything. / And IAD and PHX went **last**, / after every smaller region had run it first.
>
> So they agreed, / and IAD and PHX were enabled in the final wave, at the end of January, / starting with a subset of shards. / It ran cleanly there, with **no Sev2s from shrink**.
>
> What I learned: / when someone has paused something for a good reason, / don't argue with their reason. / Show them why your proposal doesn't have that problem, / and hand them the off switch.

### 60-second version
> After index rebuilds caused a string of Sev2s, managers **paused maintenance in IAD and PHX**, our biggest regions. / I pushed to enable my lighter Index Shrink there, / because those regions were exactly its use case. / I didn't argue the pause was wrong. / I showed that **its causes didn't apply to shrink**: no temp space, no journal tables, no redo spikes, / backed by production experiments where shrink finished even when a rebuild failed. / Then I gave them controls: a per-shard allow-list, a dry-run switch, rollback without a deploy, / and IAD and PHX **last**, after every other region. / They agreed, and both regions went live in the final wave, with **no Sev2s from shrink**.

### If the question says "your manager" (2026-11-03)
- **Name the disagreement in the first 15 seconds.** *"The disagreement was whether to run index maintenance again in our two biggest regions. `[My manager / My manager and the other managers who owned those regions]` had paused it after a run of Sev2s. I thought restarting it, with Index Shrink, was the fix, not the risk."* Then the normal script.
- **Interviewers listen for four things:** you understood their reason, you disagreed with data rather than opinion, you raised it in the right place, and the relationship was fine afterwards. The script covers the first two. Follow-ups 7–9 cover the other two.

#### Manager version, spoken (~2.5 min)
> The biggest disagreement I had with management was about **whether to run index maintenance again in our two biggest regions**, IAD and PHX.
>
> Some context. / Online index rebuilds had caused a run of incidents, / **ten auto-cuts and eleven Sev2s** in a couple of months. / So `[my manager / my manager and the other managers who owned those regions]` paused rebuilds there. / That was a reasonable call. / But it meant maintenance **wasn't happening at all** in the two regions with the most load.
>
> I'd built Index Shrink as the lightweight alternative, / and I thought those two regions were exactly its use case. / So my position was: / **restarting maintenance, with shrink, is the fix, not the risk.** / `[NEED: how you raised it and their first reaction, e.g. "I took it to my manager one-on-one with a written proposal, and the first answer was 'not yet'". Only if true]`
>
> I handled it in three ways.
>
> First, **I didn't argue that the pause was wrong.** / I agreed with the reason for it, / and argued only that the reason didn't apply to shrink. / What hurt those regions was how a rebuild uses resources: / temp space, double the disk, a journal table, redo spikes, / and contention that turned into 503s for customers. / Shrink runs in place: / no temp space, no journal table, / redo spread out instead of spiking.
>
> Second, **I brought data, not promises.** / I'd run experiments, including in production. / On moderate fragmentation, shrink took about the same time as a rebuild, without the side effects. / And on one heavily fragmented partition, / **the rebuild failed outright while shrink finished.**
>
> Third, **I treated their risk as a design requirement**, so they kept control. / A per-shard allow-list, so we could start with one shard. / A global dry-run switch. / Both changeable **without a deploy**, so they could stop it in minutes. / Alarms in place before we enabled anything. / And IAD and PHX went **last**, after every smaller region had run it cleanly.
>
> They agreed. / IAD and PHX were enabled in the final wave, starting with a subset of shards, / with **no Sev2s from shrink**, there or anywhere else. / `[NEED, only if true: "And after that, my manager left the IAD and PHX enablement calls to me."]`
>
> What I took from it: / when your manager has paused something for a good reason, / **don't fight their reason. Show why your proposal doesn't have that problem, and hand them the off switch.**

### Likely follow-ups
1. **What exactly were the managers worried about?** The same thing that caused the pause: background maintenance degrading customer traffic in regions with no headroom. *(Keep it at that unless you remember specific objections. Don't invent quotes.)*
2. **What if they'd said no?** I'd have disagreed and committed: run it in the other regions, collect a few weeks of data, and come back with it. *(Hypothetical.)*
3. **Why not just wait longer?** A pause isn't free. Maintenance had stopped entirely in our two busiest regions, so the longer we waited, the bigger the job when it restarted. *(Confirm this matches your reasoning.)*
4. **How cheap was rollback, really?** Remove a shard from the allow-list or flip dry-run, both JVM args, no deploy.
5. **Did anything go wrong there?** No. It ran cleanly in the smaller regions first, then in IAD/PHX, with no shrink-caused Sev2s through the rollout and the months after.
6. **How do you disagree with leadership without damaging trust?** Concede what's right about their position, argue only the part where you have data, and give them control of the risk.
7. **"How did you raise it with your manager?"** `[NEED: a 1:1, a design review, a written proposal?]` The strong shape, only if true: privately first, with the evidence written down, before any wider forum.
8. **"What did your manager say when you first raised it?"** `[NEED: their actual first reaction. A "no" or "not yet" makes this a real disagreement]` Don't invent quotes. *"They were cautious, which was fair after eleven Sev2s"* works only if it's what happened.
9. **"How was the relationship afterwards?"** `[NEED]` If true: they backed the wave plan, or trusted you with the IAD/PHX enablement calls.
10. **"What was your role, and how senior were you relative to those managers?"** (~45 s) *Make the power gap clear. It makes the story stronger.*
    > I was a senior engineer on the metadata team, an individual contributor, not a lead or a manager. `[NEED: exact title as on your HR record; resume says "Senior Core Infrastructure Engineer"]` Index Shrink was my project end to end: I designed it, ran the experiments, and took it through design review and operational readiness. I was also on the on-call rotation and mentoring a junior engineer.
    >
    > The people I was disagreeing with were `[NEED: my manager / my manager and my skip-level / the managers who owned those regions]`, so `[one / two]` levels above me, and they carried the operational risk for those regions. **I had no authority to turn maintenance back on. The decision was theirs.**
    >
    > That shaped how I handled it. I couldn't win on authority, so I won on evidence, and I made saying yes cheap for them: they kept the off switch, and the biggest regions went last.
    - Don't say "tech lead" unless it was your title. Don't shrink it to "just an engineer" either. 🟢 (timeline: title; your confirmation that all of Index Shrink is yours; S4 on-call; S9 mentee)
11. **"What were the concrete stakes if maintenance stayed paused? What would happen to those databases?"** (~75 s)
    > Three things, and they compound.
    >
    > **First, the indexes keep bloating.** When an object is deleted, the database doesn't remove its index entry. It just marks it deleted, and that space only gets reused if a new entry lands in the same block. Lifecycle rules and bucket migrations delete at huge volume, so dead entries pile up. When we did rebuild badly bloated partitions of our listing index in IAD, **about two-thirds of each partition was dead space.** With maintenance paused, that keeps growing, and so does disk usage.
    >
    > **Second, queries slow down, and listing is hit first.** Listing walks that index, so it reads more and more dead blocks. That shows up as SQL timeouts and failed listings. Even while rebuilds *were* running, fragmentation in lifecycle listing was causing **five to eight Sev3s a month and one or two Sev2s**, and on-call rebuilt **45 partitions by hand in IAD in one month.**
    >
    > **Third, the pause makes itself harder to undo.** A rebuild needs about **twice the partition's size free** in temp space and in the tablespace, and it won't start when the file system is close to full. The longer we waited, the bigger the partitions got, and the closer we got to a point where a rebuild couldn't run at all, in exactly the regions with the least headroom. `[Confirm: this was part of your reasoning at the time]`
    >
    > So the pause swapped a loud, immediate risk for a quiet one that compounds. That's why I didn't want to just wait.
    - **Numbers and where they come from** (team docs, not your project, so cite them as the baseline, never as your work):
      - Two-thirds dead: IAD partitions before/after a rebuild, 376 → 126 GB and 363 → 133 GB (Nov 2024). 🔵 derived: 67% and 63% smaller. Say the ratio, not the GB.
      - 5–8 Sev3 listing + 3–5 Sev3 delay + 1–2 Sev2 per month; 45 manual rebuilds in IAD in 30 days, ~2 h each, ~90 h of dev/on-call time. 🟢 (`Index rebuild OLM/Index Rebuild for Listing failur…pdf`, "Current Business Impact")
      - Rebuild needs TEMP ≥ 2× partition size and (MAX − allocated) ≥ 2× partition size; it skips at high file-system use (80–90%), and file-system use is a high watermark that bucket migration can't lower. 🟢 (same doc, safety checks and known limits)
    - **If asked "was that listing data from your project?"** No. It's from a teammate's design for auto-rebuilding partitions with listing failures. You're using it to show what fragmentation does.
    - **Optional firsthand line, only after confirming:** months later, slow versioned-metrics queries on IAD/PHX shards where rebuilds had been paused needed DBPerf and a manual rebuild (your answer of 2026-11-02). It happened *after* shrink was enabled, so expect "why didn't shrink fix it?" Answer only if you know: `[NEED: those partitions were past shrink's 300 bytes-per-row range (rebuild territory, still paused), or shrink wasn't on for those shards]`.
    - **Background: what fragmentation, rebuild and shrink actually are:**
      - **The index.** Every object is a row in `MDS_OBJECTS`. Listing uses the B-tree index `MDS_O_BUCKET_ID_OBJECT_NAME_UN` (bucket ID + object name), by far the largest: ~1 TB on a ~5.9 TB table on one IAD shard, in 64 partitions. 🟢
      - **Fragmentation.** A delete only marks the leaf entry as deleted (`DEL_LF_ROWS`). The team measures bloat as **bytes per row** (partition size ÷ rows). Ideal for the listing index is 200. Above that, the partition is carrying dead weight. 🟢 (`Understanding fragmentation…pdf`, rebuild docs)
      - **Two harms:** disk use goes up and query performance goes down. Bucket migrations and mass deletes such as OLM speed it up. 🟢 (`Index rebuild improvement plan…pdf`)
      - **Rebuild** (online, per partition) builds a brand-new compact copy of the partition from the table while tracking concurrent writes in a **journal table**, then swaps it in. Costs: TEMP plus a second copy (~2× space), heavy redo, 5–6 h per partition in IAD at >5k writes/s (12 min to 17.7 h, once 22 h, on the listing index), one at a time per database host, parallelism cut from 4 to 1 because of log-file-sync latency, and if the client host restarts mid-rebuild the work is thrown away. Result: a compact index (e.g. 285 → 129 bytes per row). 🟢
      - **Shrink** compacts the existing index **in place** by moving entries into fewer blocks: no TEMP, no journal table, redo spread out. Less effective at high fragmentation, hence the 200–300 shrink / >300 rebuild split. 🟢 (ORR)
12. **"You got an initial 'not yet'. What did you say or do to move it forward?"** (~80 s) ⚠️ *The "not yet" came from my example placeholder in the manager version. Accept the premise only if it really happened. If not, open with the honest reframe below.*
    - **If there was no explicit "not yet":** *"To be precise, it wasn't a no in one meeting. The caution was built into the pause itself. What moved it was this…"* Then the same three steps.
    > I didn't treat "not yet" as "no", and I didn't push harder in the same conversation. `[Only if true: I asked what "yet" was waiting for.]` The concern behind it was clear from the pause itself: would this hurt those regions the way rebuilds had, and could we stop it fast if it did? So I turned that into a checklist and closed it item by item.
    >
    > **First, proof.** I already had experiments, in perf and in production, showing shrink matched rebuild on moderate fragmentation without the side effects. The open question was the failure mode. So with our DBPerf expert, we deliberately corrupted an index block in testing, and I made shrink detect that error and fall back to a single rebuild.
    >
    > **Second, a smaller ask.** I stopped asking "can we turn it on in IAD and PHX?" and asked them to approve a plan instead: ship it dark to every region, turn it on in the small regions first, one or a few shards at a time, and leave IAD and PHX for the very last wave. That way the IAD/PHX decision would be made on evidence from every other region, not on my word.
    >
    > **Third, the off switch in their hands.** A per-shard allow-list and a global dry-run, both JVM arguments, so stopping it needed no deploy. And alarms in place before anything was enabled.
    >
    > By the time IAD and PHX came up, it had run in every other region without a shrink-caused Sev2, and "not yet" became "yes".
    - 🟢 Evidence: experiments (May–Aug 2025, perf + EU-Paris); corruption test with DBPerf (ORR: Jim McCann "collaborated on inducing the index block corruption"); ORA-01578 → mark failed → one partition-level rebuild (ORR); shipped dark in MDS 5.10 to all regions (13 Oct 2025); waves from 5 Dec with IAD/PHX last (planned 30 Jan 2026); allow-list + dry-run via JVM args; alarms before enablement; no shrink Sev2s (your answer).
    - **Don't add (follow-up 12):** escalating past your manager, or a specific meeting or quote you don't remember. "The concern behind the pause" is fair and true. Don't make the timeline sound like it all happened in response to one "no" if the dark launch was always the plan; *"I shaped the rollout around that concern"* covers both.
13. **"Beyond zero Sev2s, what measurable impact did running maintenance in IAD/PHX have: fragmentation, query performance, disk?"** (~70 s) *There's no post-enablement IAD/PHX number in your files. Don't invent one; lead with what's real.*
    > Honestly, the result I can stand behind is operational: maintenance running again in our two biggest regions, with no Sev2s from shrink. I don't have a clean before-and-after for disk or latency in IAD and PHX, and I'd rather tell you that than estimate one.
    >
    > What I can measure is what each operation did, because that's exactly what the pause was about. In our production experiments, on a 36-gig partition, **shrink's redo peaked at about 12 megabytes a second. A rebuild of the same partition had peaked at about 130, roughly ten times higher.** Redo spikes were one of the main reasons maintenance was paused. On moderately fragmented partitions, shrink also finished in the same time as a rebuild, with no temp space and no second copy of the index.
    >
    > And it's tracked per partition: every shrink records its outcome in a history table and publishes bytes per row, so `[NEED: what you actually saw in IAD/PHX, e.g. how many partitions were shrunk, or that partitions drifting up during the pause came back under the 300 line]`.
    - 🟢/🔵 **Redo numbers:** `Executive Summary of Index Shrin…pdf`, prod experiment, 36.1 GB partition: dashboard legend max **11.75 MiB/s** during shrink vs **129.63 MiB/s** for the rebuild of the same partition (13 Aug 2025). ~11× lower peak (🔵). Read from screenshot legends: **open the PDF and confirm the two numbers before quoting.** The second chart is labelled sa-santiago-1, though the page heading says EU-Paris, so just say "in production".
    - 🟢 Time parity: 21 GB / 30% deleted: shrink 14+1 min vs rebuild 14 min. History table `INDEX_SHRINK_HISTORY` (ORR). Metric `mds.rebalancer.index.shrink.bytes.per.row`.
    - **Pattern risk:** don't close with "next time I'd measure a baseline" if you've already used that lesson in S2, S1 or S7 in the same loop. Three of your stories already end with it.
    - **If pushed ("so how do you know it helped?"):** the regions stopped accumulating dead space with nothing reclaiming it, and the operation that does the reclaiming no longer spikes redo. That's true without a fleet number.
14. **"Looking back, what would you do differently: the technical case, or navigating the disagreement?"** (~75 s) *Not the "baseline metrics" lesson again (S1/S2/S7 already use it).*
    > Two things, one on each side.
    >
    > **On the technical case, I'd make the case for the whole problem, not just the part my feature solved.** Shrink is built for moderate fragmentation. Partitions past the rebuild line still need a rebuild. I argued for shrink in IAD and PHX and won that, but rebuilds there stayed paused, so the most fragmented partitions still had nothing reclaiming them. I saw the cost months later, when queries for a feature I was shipping ran slowly on heavily fragmented shards there, and we had to bring in DBPerf and rebuild by hand. Next time I'd bring the full picture: shrink for the moderate cases, and a concrete plan for when and how rebuilds come back for the heavy ones.
    >
    > **On the disagreement, I'd agree the go/no-go criteria for each wave with my manager up front, in writing.** We had a staged plan with dates, but moving to the next wave was still a judgment call each time. If we'd agreed beforehand what "clean" meant (no shrink-caused incidents, redo within a set limit, no corruption errors), then reaching IAD and PHX would have been a decision we'd already made together, not a fresh negotiation.
    >
    > What I wouldn't change is pushing back on the pause. That was right. I'd just make sure I'm winning the argument for the whole problem, not only for my feature.
    - 🟢 Shrink's limit: ORR "Limitations" (heavily fragmented → rebuild preferred) and the 200–300 shrink / >300 rebuild split. 🟢 Slow versioned-metrics queries on fragmented IAD/PHX shards after months of paused rebuilds → DBPerf → manual rebuild (your answer of 2026-11-02).
    - `[Confirm: rebuilds really stayed paused in IAD/PHX after shrink went live (your 2026-11-02 answer implies it). If rebuilds came back for >300 partitions, drop the "stayed paused" line and keep only "I'd have argued for the full plan from the start".]`
    - 🟢 The ORR wave plan has dates and a status column, no go/no-go criteria; "SRE/Ops Review and Readiness" is TO DO. `[Confirm: wave-to-wave decisions really were judgment calls. If written criteria existed elsewhere, use only the technical lesson.]`
    - **Why it works:** both lessons are about scope and agreement, not "I'd measure more". The last line shows conviction: you'd still challenge the pause.
15. **"Have you applied either lesson since?"** (~60 s) *Honest answer: one yes, one not yet.*
    > Partly, and I'll be precise about which.
    >
    > **The full-problem framing, yes,** on the next design I did after the shrink rollout: per-bucket metrics for versioned objects for a strategic customer. I chose to compute them at query time instead of building a pre-aggregated summary table, because that kept us off the write path and inside the deadline. But I didn't present it as the final answer. The design spelled out where it stops working, from about two minutes at today's scale to over twenty minutes at ten thousand buckets on one shard, and named the summary table as the way to go if adoption grew past that. So the people signing off saw the whole problem, including the part we were deliberately leaving for later.
    >
    > **The go/no-go criteria, honestly, not fully yet.** That rollout was gated: one customer, behind a flag, configured namespaces only. But those were scope limits, not written pass/fail criteria for widening it. That's the one I'll write down with my manager before the first stage of the next rollout I lead.
    - 🟢 S1 / HLD: query-time aggregation vs summary table; 700 buckets 1.6 min warm / 2.7 min cold; 10K on one shard 22.2 / 23.4 min; summary table as the documented next step (a scale point, not a formal trigger). ORR: release limited to one customer, flag `emitVersionedBucketMetrics`, configured namespaces only.
    - ⚠️ **Timeline trap:** in follow-up 14, "I saw the cost months later" *is* the versioned-metrics project. So don't say the HLD was designed *because of* that cost. Say "the next design I did after the shrink rollout" (shrink waves to 30 Jan 2026; versioned-metrics M0 27 Mar 2026). `[Confirm: you were already thinking "show the whole problem" when you wrote the HLD]`
    - `[Confirm: no written go/no-go criteria for widening the versioned-metrics release (the ORR shows none: "Risks: N/A", alarms "TO DO")]`
    - **Story reuse:** if S1 was already told in this loop, say "the metrics project I mentioned" and keep it to two sentences.
    - **Why it works:** "one yes, one not yet" sounds credible. Claiming both would sound rehearsed, and the second claim has no evidence.

### Weak spots & risks
- **Same project as S2 and S8.** In one loop, tell this as the conflict story and keep S2 for "Highest Standards / Invent and Simplify", only if asked for another example.
- You don't have the managers' exact objections. Keep their side as "the reason for the pause". That's fair and true.
- **"Your manager" vs "managers".** The files say *managers* paused it. `[NEED: was your direct manager one of them?]` If not, say "my manager and the other managers who owned those regions". Don't turn a group decision into a one-on-one clash.
- **Was it a disagreement or a proposal?** If they agreed the first time you asked, a Bar Raiser will hear persuasion, not disagreement. The story needs a moment of pushback (follow-up 8).
- **Next question is often "a time you lost the argument".** S6 is a win. That's gap G1, still open.

**Sources:**
- `Index Shrinks/Index Shrink Operational Readine…pdf` (problem statement, paused regions, key features, rollout waves, rollback)
- `Index Shrinks/Executive Summary of Index Shrin…pdf` (experiments)
- `Index Shrinks/Index Shrink Design Proposal_…pdf`
- your answer of 2026-11-01 ("managers had paused… I asked to enable this feature")

---

## S7 · My Java 17 upgrade caused a performance regression (failure #1)

**Hook:** I owned moving our lifecycle service from Java 8 to 17. It compiled and passed tests, and then perf2 showed a regression that took me **about 8 weeks** to pin on a TLS default that wasn't on anyone's checklist.

| | |
|---|---|
| **Amazon LPs** | Primary: **Ownership**, **Learn and Be Curious** · Secondary: Dive Deep, Insist on the Highest Standards, Deliver Results |
| **Google attributes** | Growth mindset · Intellectual humility · Comfort with ambiguity |
| **Tilt** | **Amazon ★★★** (owning your own miss and the mechanism you changed) · **Google ★★** (stress what you learned and changed) |

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

### Perseverance version (~2.5 min): "significant technical obstacles, kept pushing" 🟢 (your answers of 2026-11-01/02)
> In 2024 I owned moving our metadata services from Java 8 to 17. / It landed together with two other platform mandates: / a new deployment platform, and a FIPS-certified crypto library called Jipher. / Each service broke in its own way: / API changes, module-access flags, dependency versions. / I worked through those with two junior engineers helping, / and everything compiled and passed tests.
>
> Then perf2 load testing showed us **two different performance problems**. / One was loud, and one was quiet.
>
> **The loud one was garbage collection.** / We'd moved from G1 to **ZGC**, the low-pause collector, / and under load we saw **CPU spikes and a drop in throughput**. / ZGC on Java 17 isn't generational, / so for services that create lots of short-lived objects, / it can burn more CPU than the pauses it saves. / I didn't want to throw away the whole upgrade over one setting, / so we **switched back to G1 through configuration**, kept Java 17, / and re-qualified.
>
> **The quiet one was harder.** / We still had a **latency regression** against our Java 8 baseline, / and **nothing in our hot-path code had changed**. / So I went after it methodically. / I added targeted logging, / and I shortened my own loop: I skipped integration tests in the perf builds, / so each experiment came back faster. / First I checked whether we were simply **doing more work**: / I put checkpoint logs through startup, the scheduler, the cache build and tenant listing, / and printed tenant counts. `[Confirm what they showed, e.g. "same work, just slower"]` / Then I cleared out the things Java 17 had legitimately broken, / the dependency-injection library version, module-access flags, our client library versions, / so they couldn't muddy the picture. `[Confirm these were part of the hunt]` / Since our code hadn't changed, / the change had to be in the platform: the new runtime or the new crypto provider. / That's where I found it, in the **TLS layer**. / Newer Java sends a session ticket when it reconnects, / and with the Jipher provider, resumption didn't succeed, / so **every reconnect fell back to a full handshake**: / expensive crypto, on every connection.
>
> The fix was two JVM flags: / fall back to session-ID resumption, / and offer only the key-exchange curves Jipher supports. / We re-qualified again and shipped.
>
> It took about **eight weeks** from my first debugging build to the TLS fix, / and with two re-qualifications, **the release slipped**. / But we caught both problems in perf2, not in production, / and we stayed on Java 17 rather than rolling back.
>
> What I took from it: / when your code hasn't changed, look at what the **platform** changed, especially its defaults. / And we changed too many things at once, / a new JDK, a new GC and a new crypto provider. / Today I'd change **one variable at a time** against a baseline, / so each regression points at its own cause.

**Why this works for perseverance:** two separate obstacles with different shapes, a hunt with a method (a faster loop, ruling things out), and alternatives you *didn't* take: rolling back to Java 8, or shipping with the regression. It also admits the cost (the slip) and gives a concrete lesson. **One gap:** the dead ends. "What did you try first?" is the most likely follow-up.

### Leadership version (~3 min): "led a team through a high-pressure / high-stakes situation" (2026-11-03)
*Same facts, told as leading. Use only one S7 version per loop. If S7 is told here, use S8 for "a time you failed".*
> In 2024 I owned moving our metadata services from Java 8 to Java 17. / It was an **org-wide mandate**: Java 8 support was ending, and management had set a **hard deadline**. / It landed at the same time as two other platform mandates, / a new deployment platform and a FIPS-certified crypto library. / Two junior engineers were working with me. / `[How you split the work, e.g. "I took the services with the riskiest dependencies and gave one of them ownership of the test phases."]`
>
> The code side went well. / We worked through each service's API breaks, module-access flags and dependency versions, / and everything compiled and passed tests. / Then our performance testing hit us **twice**: one problem was loud, and one was quiet.
>
> **The loud one was the garbage collector.** / Along with Java 17, we'd switched from G1, the default collector, to **ZGC**, the low-pause one. `[Why: e.g. "to cut GC pauses for tail latency"]` / Under load it caused **CPU spikes and a drop in throughput**. / On Java 17, ZGC isn't generational, / so with lots of short-lived objects it can burn more CPU than the pauses it saves. / There was pressure to roll the whole upgrade back, / but I didn't want to throw away Java 17 over one setting. / So we **switched back to G1 through configuration**, stayed on Java 17, and re-qualified.
>
> **The quiet one was the high-stakes moment.** / We still had a **bad latency regression** against Java 8, / with no obvious cause in our code, / in the service that runs customers' lifecycle rules, deleting and archiving their data across the fleet. / The deadline was real, / but shipping a fleet-wide latency regression to meet it was worse. / **I held the rollout.** `[How you told management and who agreed, e.g. "I told my manager the same day, with what we knew, what we didn't, and when I'd update them."]`
>
> Then I organised the team so we kept moving. / I took the root-cause hunt myself: / targeted logging, and a faster build loop so each perf experiment came back sooner. / `[What the juniors owned meanwhile, e.g. test phases and status updates.]` / After about **eight weeks**, I found it in the **TLS layer**. / Newer Java resumes connections with session tickets, / and with our new crypto provider that resumption failed, / so **every reconnect did a full, expensive handshake**. / **Two config flags** fixed it.
>
> **The release slipped.** Two re-qualifications will do that. / But we **never shipped either regression**, / we stayed on Java 17 rather than rolling back, / `[What the juniors got out of it, e.g. one of them went on to own X.]`
>
> What I took from it as a lead: / under deadline pressure, **separate what's mandated from what's optional**. / Java 17 was mandated; ZGC was optional, / and bundling them cost us a whole re-qualification. / And when the stakes are customer-facing, / **holding is a decision you own and explain, not a delay you apologise for.**
- 🟢 Facts: mandate + hard deadline + Java 8 end of support (your answer of 2026-11-02); Prism + Jipher + Java 17 together; two juniors; your 22 Apr 2024 commit switched OLM from G1 to ZGC; CPU spikes + throughput drop → back to G1 by config, no rollback to Java 8, re-qualified (your answer of 2026-11-02); perf2 latency regression, rollout held, ~8 weeks to the TLS fix (24 Jul 2024), release slipped.
- ⚠️ **"There was pressure to roll the whole upgrade back"** is only a line if it's true. If nobody suggested it, say "Rolling back to Java 8 would have been the easy option".
- ⚠️ **ZGC evidence check** (S7 weak spots): OLM's start script still defaults to ZGC at HEAD (Jul 2025). Be ready to say where the switch back to G1 happened (deploy override, or other services).
- **Leadership slots matter most:** how you split the work, how you told management, what the juniors owned and gained. Without them this is the perseverance story again.

### Likely follow-ups
1. **Why did it take 8 weeks?** [From memory: honest answer: competing priorities? slow perf2 cycles? red herrings you chased?] Have one red herring ready. It makes the debugging real.
2. **How did you narrow it to TLS?** [From memory: e.g., profiling showed handshake CPU? per-connection latency? comparing JDK 8 vs 17 on the same build?]
3. **Why disable session tickets instead of fixing the provider?** The provider is a platform dependency we don't own. JVM flags gave a safe, reversible fix right away. [From memory: did you file it with the Jipher/platform team?]
4. **Did other services hit the same issue?** [From memory: did you share the fix? If yes, that's a "Success and Scale" bonus.]
5. **How did the juniors help?** → S9.
6. **What would you do differently from day one?** Baseline before the change, and A/B the same build on JDK 8 vs 17 in perf2 first, so a regression shows up in days, not weeks.
7. **Isn't disabling session tickets a security trade-off?** Session IDs are still a supported resumption mechanism. [From memory: did security review it?]
8. **"Why did the TLS problem happen, and what's the proper fix?"** Since JDK 13, Java clients send the **session-ticket extension** by default (stateless resumption). With the Jipher FIPS provider, resumption didn't succeed, so **every reconnect fell back to a full handshake** (documented in the commit). The *exact* reason the two didn't work together isn't in the commit, so don't invent one. Long-term options: provider support for ticket resumption (owned by the platform/crypto team), and **connection pooling / keep-alive** so fewer handshakes happen at all. The flags were the safe, reversible fix you controlled.
9. **"Why try ZGC, and why revert instead of tuning it?"** What you saw: **CPU spikes and lower throughput** in perf2. 🟢 Why you tried it: `[NEED]`. Revert reasoning, if true: *"On JDK 17 ZGC isn't generational. Under our allocation rates it cost more CPU than the pauses it saved. G1 met our latency needs, and reverting was a config change, so it was the low-risk call. Generational ZGC in JDK 21 is worth retrying."*
10. **"What was the business impact if the migration had failed or been abandoned?"** Context (your answer of 2026-11-02): **Java 8 support was ending**, there was an **org-wide mandate** to move to Java 17 and a newer stack, and **management set a hard deadline** after it had been "a long time coming". 🟢
   - **Security:** metadata services on a runtime that no longer gets security patches. Not acceptable for a storage service holding customer data.
   - **Falling behind the platform:** the newer stack moves on. Staying on 8 means pinning old library versions, and the jump gets bigger every quarter.
   - **The deadline:** org-wide and set by management, so missing it on a core service is visible. `[If true: other teams depended on our client libraries moving]`
   - **The second way to fail:** making the deadline by **shipping the regressions** (full TLS handshake on every reconnect, ZGC's CPU spikes) = a fleet-wide CPU and latency hit in production. The real trade-off was **slip the release vs ship a regression**. You chose the slip, fixed narrowly, and stayed on 17.
   - `[NEED: did you still land before the org deadline despite the release slip?]` This decides how you close the answer.
   - Careful: the TLS commit is in **OLM**, a background lifecycle service. Don't say "the path every request goes through" about that regression.
11. **"What specific steps did you take to narrow it down, and how did you decide what to try next?"** From the OLM git log (30 May – 24 Jul 2024, your commits): 🟢
   - **30 May:** "Debugging perf2 issue": checkpoint logs in `LifecycleEngineServer` / `ScheduledProcessorService`; **ITs skipped in the PR build** so each experiment produced a tag faster.
   - **31 May:** logs through `LifecycleEngineCache` and tenant listing (`tenantMdsClient`, `NamespaceLister`), printing **tenant/namespace list sizes**. Question: *more work, or the same work slower?*
   - **19 Jun – 2 Jul:** correct Guice version, `--add-exports/--add-opens` everywhere, aligned `casper-shared`, `webserver-v2-client`, `mds-clients` versions. `[Confirm: part of ruling suspects out, or routine migration?]`
   - **24 Jul:** TLS fix. Your commit message names the mechanism: full handshake on every resumption.
   - **Decision rule to state:** (1) more work vs slower work, the cheap check first; (2) remove the known Java 17 breakages so they can't add noise; (3) the code hasn't changed, so look at what changed **underneath outbound calls**: JDK TLS defaults and the new crypto provider.
   - `[NEED: what the logs showed (e.g., same tenant counts, time spent in calls to other services), and how you saw full handshakes (TLS debug logging such as javax.net.debug? a profiler?). Only say what you did.]`
12. **"Any numbers for Java 17 vs the Java 8 baseline once both fixes were in?"** None in the files (the commit messages have no numbers, and there's no perf report). Answer:
   - *"I don't have exact figures to quote. The regression was bad enough that we held the rollout. After the GC change and the TLS flags, the build **passed the same perf2 qualification against the Java 8 baseline** that had caught it, and that was our bar to ship."* `[Confirm it passed against the baseline]`
   - Add a rough number **only if you genuinely remember one** (e.g., "ZGC pushed CPU from about X to Y").
   - **Don't add another "I'd record numbers next time" lesson here.** S1 and S2 already lean on that, and three of them reads as a pattern.
13. **"Why not just roll back to Java 8?"** You didn't. 🟢 *"Java 17 was a platform mandate, so rolling back would only postpone the problem. Each issue had a narrow fix (one GC setting, two TLS flags), so we kept the upgrade and fixed those."*
14. **"Beyond one variable at a time, what changed in how you approach migrations?"** Three changes:
   - **Separate the must-have from the nice-to-have.** Java 17 was mandated. ZGC was optional, and you bundled it into the same commit (22 Apr 2024, OLM git), which cost a re-qualification. Now: land the mandate first, experiment after. 🟢 `[If ZGC was a platform recommendation rather than your call, reword]`
   - **Treat changed defaults as part of the diff.** Read release notes for *changed defaults* (TLS resumption, GC), not just removed APIs, and add explicit checks (a TLS handshake check, GC logs) to the upgrade checklist. `[Only if true for you]`
   - **Make every risky knob reversible by config, and stage it.** Both of your recoveries were config-only (a GC setting, two TLS flags), which is why Java 17 survived. *Applied:* Index Shrink, 2025: shipped dark in MDS 5.10, global dry-run plus per-shard allow-list via JVM args, region waves with the biggest last. 🟢 (ORR) Also the versioned-metrics feature flag and limited release.
   - **Close:** *"Migrations fail in the parts you didn't think you were changing."*
15. **"How large was the fleet you were migrating, and what was the business impact if the lifecycle service had shipped with that latency regression?"** (~70 s) *Complements follow-up 10 (mandate / slip vs regression).*
   > It was **all of our MDS-related services**, `[roughly N: e.g. "the metadata service itself, the lifecycle engine and the services around them"]`, each with its own breakages. The latency regression showed up in the lifecycle service.
   >
   > If we'd shipped it, the impact would have come in three layers. **First, customers' own rules would run late.** The lifecycle service is what deletes old versions and archives data on schedule, so a slower service means that work falls behind: customers keep paying to store data their rules say should be gone, and retention rules get applied late. We already got lifecycle-delay tickets every month for other reasons, so this would have added to a known pain point.
   >
   > **Second, it wasn't only the lifecycle service paying.** A full TLS handshake costs CPU on both sides, so every reconnect also cost the metadata servers that handle customer requests.
   >
   > **Third, scale.** The lifecycle service runs across the whole fleet, so this would have been a CPU and latency hit everywhere, worst where there's the least headroom.
   >
   > Against that, holding meant a visible slip on an org-wide mandate. That was a cost to us; shipping the regression would have been a cost to customers. That's why I held.
   - 🟢 "All MDS-related services" (your answer of 2026-11-03). `[NEED: the count or names. Don't list services you didn't migrate]`
   - 🟢 OLM runs customers' lifecycle rules (deletes, archival) across the fleet (S7 situation). 🟢 Lifecycle-delay tickets: the team's OLM listing-failures doc records "3–5 Sev3 OLM-delay issues per month" (a teammate's doc; a different cause). 🟢 Full handshake on every reconnect (TLS commit, 24 Jul 2024).
   - 🔵 Server-side CPU cost of full handshakes and the fleet-wide effect are reasoning, not measured. Say "would have", never "did".
   - ⚠️ **Expect: "Did the TLS issue affect the other services too?"** The fix is only in OLM's git. `[NEED: was it OLM-only, or did other services need the same flags?]`
   - **Don't** quote a CPU percentage, a dollar figure or a customer count.
16. **"While you owned the investigation, how did you keep the two juniors productive and motivated through eight weeks of uncertainty?"** (~75 s) *Built from real S9 facts (Action 6). Nothing invented; brackets are things only you can confirm.*
   > Two things mattered: they needed work that **wasn't blocked by my investigation**, and they needed to know the hold **wasn't a failure on their part**.
   >
   > On the first: we'd held the rollout, not the project. `[What they kept doing, e.g. "they carried on with the remaining services' migrations".]` One of them **owned the test phases**: running the qualification cycles and **reviewing the results with me**, so every experiment I ran had someone checking its effect.
   >
   > On the second: `[Only if true: I was explicit that the regression came from the platform, a new runtime and a new crypto provider, not from anything they'd written, and I shared what I was ruling out as I went, so they could see progress even before we had the answer.]`
   >
   > And I **coached their status updates**: what's done, what's at risk, what they need. Through eight weeks of uncertainty that mattered. They could report clearly instead of just saying "still blocked".
   >
   > In hindsight, I kept the most interesting part, the hunt itself, to myself. It was the best learning opportunity on the project. `[Only if the link is real for you: The next year, on the lifecycle rate limiter, I did the opposite: I designed it and handed my mentee the build, and they were promoted on it.]`
   - 🟢 S9 Action 6 (your answer): second junior across Java 17 / paginated GET / Uber metrics: ownership of test phases, reviewed results together, coached status updates ("what's done, what's at risk, what they need"). 🟢 S9: rate limiter (Mar 2025) designed by you, built by your SD1 mentee, promoted Aug 2025.
   - **Memory prompts (to recall, not invent):** Did they keep migrating other MDS services during the hunt? Did either of them run perf2 cycles for your experiments? What did you tell them when the rollout was held? Did they sit in on any debugging? Did either get visible credit (a demo, a status mail)?
   - **The hindsight line is the strongest part.** It's an honest self-critique, and the S9 link shows you changed. Use the S9 link only if you really see it that way, and keep it to one sentence if S9 is told in the same loop.
   - **Don't add:** team rituals, 1:1 cadences, morale events or quotes you don't remember.
17. **"Once you shipped, what were the concrete outcomes: latency, CPU, how leadership received it?"** (~60 s) 🟢 monitoring approach (your answer of 2026-11-03)
   > Honestly, I don't remember the exact latency or CPU numbers well enough to quote them, and I won't guess. What I can tell you is how we made sure it was right. Before rollout, the release `[Confirm: passed the same load-test qualification against the Java 8 baseline that had failed before]`. After rollout, we kept a **tight watch on our KPIs in Grafana**, latency in particular, and on the **alarms for exactly the latency problems we'd hit in testing**. `[Only if true: None of them fired, and the KPIs stayed in line with what we'd had on Java 8.]`
   >
   > On leadership: `[What's true, e.g. "the mandate was closed out for our services" / feedback from your manager / nothing formal. If nothing formal, say so]`.
   >
   > The outcome I'd point to: we got through **three platform mandates at once**, a new runtime, a new deployment platform and a new crypto provider, **without shipping either regression**, and we stayed on Java 17.
   - 🟢 Monitoring after rollout: Grafana KPIs + alarms for the earlier latency issues (your answer). 🟢 Prism + Jipher + Java 17 together; both regressions caught in perf2; no rollback to Java 8.
   - `[NEED: did any latency alarm fire after rollout? did the org deadline get met despite the slip? any leadership feedback?]`
   - **Don't say "we had no baseline".** You *did* have one: the regression was measured against the Java 8 baseline in perf2. The gap is that you don't remember the numbers.
   - **Don't** close with "next time I'd record the numbers": S1, S2 and S7 already lean on that lesson.
18. **"Beyond mandated vs optional, what did this teach you about your leadership style: how you make and communicate hard calls under pressure?"** (~75 s) *Reflection, not new facts. Brackets mark the parts only you can confirm.*
   > Three things.
   >
   > **First, I sort hard calls by who pays if I'm wrong, and by whether I can undo them.** We had two calls in that project. Switching the garbage collector back was cheap and reversible, a config change, so I made it fast. Shipping with the latency regression would have put the cost on customers across the fleet, so I slowed down and held, even with a mandate deadline. A slip costs us; a regression costs customers. That's become how I decide under pressure.
   >
   > **Second, the call was the easy part; communicating it under uncertainty was harder.** `[Only if true: What I learned is to say early what we know, what we don't, and when I'll update next, instead of waiting until I have the root cause.]` Holding a mandated release is only defensible if people hear it from you first, with the reasoning.
   >
   > **Third, under pressure my instinct is to carry the hardest part myself.** I took the root-cause hunt alone. That felt like ownership, but it made me the bottleneck, and it kept the best learning on the project away from the two juniors. `[Only if the link is real: On my next big design, the lifecycle rate limiter, I handed my mentee the build instead.]`
   >
   > So my leadership style, honestly: **make the call early, explain it plainly, and don't carry all of it alone.**
   - 🟢 The two calls: ZGC → G1 by config (reversible) and holding the rollout over the latency regression (your answers of 2026-11-02/03). 🟢 You took the hunt yourself (leadership version; debugging commits). 🟢 S9 rate limiter: designed by you, built by your mentee (Mar 2025).
   - **Consistency across stories:** the "who pays if I'm wrong" test also closes S1 and drives S14. That's fine as a stable decision style, but don't use the same sentence word for word in two answers in one loop.
   - **Don't** claim a communication habit (daily updates, a written status) you didn't actually do. If the second point isn't true for you, keep only points one and three.

### Weak spots & risks
- **ZGC evidence check (OLM git):** your Java 17 commit (22 Apr 2024) changed OLM's start script from `-XX:+UseG1GC` to `-XX:+UseZGC`, and the **latest commit in your snapshot (Jul 2025) still defaults to ZGC** (`GC_JVM_ARGS` can be overridden at deploy time). So the revert to G1 was either a **deployment-config override** or in **other MDS services**. Say exactly which. `[NEED]`
- **ZGC:** say only what you saw. The non-generational / load-barrier / allocation-stall points are general reasons, not your measured cause, unless you confirm them.
- **No latency number.** "Bad enough that we held the rollout" is true and enough. The slipped release is the real cost; say it plainly, don't soften it.
- Make sure the "learning" is **real**. Bar Raisers ask "give me an example of when you applied that since". Candidates: the Index Shrink experiments-first approach (S2); the Uber metrics measurements (S1).

**Sources:** OLM git history (`olmgit/casper-lifecycle-engine`): commits by Shivang Badola on 2024-03-14 (CASPER-34390/34392), 2024-04-22 (CASPER-36221), 2024-05-30 ("Debugging perf2 issue…"), 2024-06-19, 2024-06-30, 2024-07-02, **2024-07-24 (TLS fix, full message)**, 2024-08-13. Also `Shivang_Badola_Resume.pdf` and your answer of 2026-11-01.

---

## S8 · My first Index Shrink rule was wrong (failure #2 / "a time you were wrong")

**Hook:** My first design chose between shrink and rebuild by **partition size**. My own experiment showed same-size partitions needing opposite treatment, and under my rule one of them would have been sent to a rebuild that **failed**.

| | |
|---|---|
| **Amazon LPs** | Primary: **Are Right A Lot** (seeks to disconfirm), **Dive Deep** · Secondary: Learn and Be Curious, Insist on the Highest Standards |
| **Google attributes** | **Intellectual humility** · Growth mindset · Data-driven decisions |
| **Tilt** | **Google ★★★** ("tell me about a time you changed your mind") · **Amazon ★★** (fine for "time you were wrong"; too small for "biggest failure") |

### Situation & Task (~20%)
- Designing Index Shrink (S2), I needed a rule for when to shrink vs rebuild. 🟢
- **My first design:** **10–15 GB → shrink; over 15 GB → rebuild** (configurable). Intuition: bigger partition, bigger job, so rebuild it. 🟢 (design proposal, original condition)

### Action (~60%)
1. **Ran experiments on real partitions** (May–Aug 2025). Four partitions of **21–25 GB**, all in the "rebuild" bucket under my rule, gave **opposite answers**: 🟢
   - 21 GB at bytesPerRow 234: shrink as fast as rebuild (15 vs 14 min) with none of the side effects
   - 24.7 GB at bytesPerRow 402: rebuild clearly better (11 vs 31 min)
   - **24.5 GB at 63% deleted: rebuild failed outright (OBJMDS-8494); shrink completed**
2. **Admitted the rule was wrong**, not just mistuned. Size didn't predict the right action; **fragmentation** did. My rule would have sent that 63%-deleted partition to the operation that failed. 🟢
3. **Changed the signal:** bytesPerRow deviation from the ideal (200 → 300 → shrink; above → rebuild), configurable per region. I documented the change in the design ("Change in condition") so reviewers could see both rules and why. 🟢
4. [From memory: what made you test same-size partitions with different fragmentation, and did anyone else spot it first?]

### Result + learning
- 🟢 Nothing shipped with the size rule. The bytesPerRow rule is what shipped in MDS 5.10.
- **Learning:** I'd anchored on the **easiest thing to measure** (size) instead of the **mechanism** (what makes rebuild expensive or risky is fragmentation and deleted rows). Now I derive the metric from the mechanism, then deliberately test cases built to **break** my rule.

### Spoken script (~2 min)
> When I was designing Index Shrink, / I needed a rule for when to shrink an index and when to fully rebuild it. / My first design used **partition size**: / ten to fifteen gigs, shrink; above fifteen, rebuild. / It felt obvious. Bigger partition, bigger job.
>
> Then I ran experiments on real partitions, / and four partitions of almost the same size, twenty-one to twenty-five gigs, / **all "rebuild" under my rule**, / gave me opposite answers. / On one, shrink was as fast as rebuild, with none of the side effects. / On another, rebuild was three times faster. / And on the one with sixty-three percent of rows deleted, / **the rebuild failed outright**, / while shrink completed. / So my rule would have sent that partition straight to the operation that failed.
>
> That's when I accepted the rule wasn't mistuned. It was **wrong**. / Size didn't predict anything; fragmentation did. / So I switched to bytes-per-row against the ideal, / up to fifty percent above ideal, shrink; beyond that, rebuild, / configurable per region. / And I kept both versions in the design doc, / so reviewers could see what changed and why.
>
> Nothing shipped with the old rule, / but it taught me something I use all the time: / I'd picked the **easiest thing to measure**, not the thing that **causes** the cost. / Now I start from the mechanism, / and I specifically test the cases designed to break my rule.

### 60-second version
> My first Index Shrink design chose shrink versus rebuild by **partition size**. / Then my experiments showed four partitions of nearly the same size, all "rebuild" under my rule, needing opposite treatment. / On the one with 63% rows deleted, **the rebuild failed outright**, and shrink worked. / So the rule wasn't mistuned, it was wrong: / fragmentation, not size, drives the cost. / I switched to bytes-per-row against the ideal, kept both versions in the design doc, / and since then I pick metrics from the mechanism, not from what's easy to measure, / and test the cases built to break my rule.

### Likely follow-ups
1. **Why did you pick size first?** It's on every dashboard and it correlates with job duration. Easy to measure, and wrong as a predictor of the right *action*.
2. **Would the size rule have caused an incident?** 🔵 Under it, the 63%-deleted 24.5 GB partition goes to rebuild, which failed in the experiment. So, at minimum, failed maintenance and the cleanup tickets that come with it.
3. **How do you avoid anchoring now?** Start from the mechanism, then try to break the rule with adversarial cases before I write it into a design.
4. **Who reviewed the change?** [From memory: DBPerf (Jim McCann)? ARB?]
5. **Is bytesPerRow perfect?** No. It's a proxy too, which is why every threshold is configurable per region.
6. **Tell me about a failure with real cost.** → S7.

### Weak spots & risks
- **Caught at design time, so small.** Use it for "time you were wrong / changed your mind". Don't use it as your only failure.

**Sources:** `Index Shrinks/Index Shrink Design Proposal_…pdf` (original size condition + "Change in condition"), `Index Shrinks/Executive Summary of Index Shrin…pdf` (experiment table), `Index Shrinks/Index Shrink Operational Readine…pdf` (final thresholds)

---

## S9 · Designing OLM's per-shard rate limiting and growing my mentee to SD2 through it

**Hook:** My mentee needed high-impact work to move from SD1 to SD2. I designed per-shard adaptive rate limiting for our lifecycle engine, handed them the build, and coached them through it, reviewing with questions instead of fixes. It shipped, and they were promoted.

| | |
|---|---|
| **Amazon LPs** | Primary: **Hire and Develop the Best**, **Strive to be Earth's Best Employer** · Secondary: Ownership, Invent and Simplify, Earn Trust, Deliver Results |
| **Google attributes** | Leading without authority · Growth mindset (for others) · Inclusivity (growing people, not just assigning tickets) |
| **Tilt** | **Amazon ★★★**: mentoring is a basic qualification for this role, and this story has a real design plus a promotion. **Google ★★★**: a noisy-neighbour design plus how you grew someone. |

> **How to tell it honestly.** 🟢 Git shows the implementation is your mentee's: CASPER-48918 and CASPER-48919 (Mar 2025) and the April adjustment fix. 🟡 The design is yours (your answer of 2026-11-01). Say "**I designed it, my mentee built it, I reviewed every change**". Never say "I built it". **Fix your resume line** from "Built per-shard adaptive rate limiting" to "Designed… (implemented with a mentee I coached to promotion)".

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

### Likely follow-ups
1. **How much was you vs your mentee?** I designed it and reviewed every change. They implemented and tested it, and both tickets are theirs. (Say this plainly. It's the honest answer, and it makes the mentoring credible.)
2. **Why per shard, not per tenant?** The shard is the physical bottleneck. One tenant spans many shards, and many tenants share a shard, so a per-tenant limit can overload a hot shard while leaving capacity unused elsewhere.
3. **Why multiplicative increase rather than additive (AIMD)?** It recovers quickly after a cut, and the increase only happens when ≥80% of the allowance was actually used, capped at 10,000/s. The hold band between the thresholds damps oscillation. *(This is the design's logic; give your own words.)*
4. **Why 5-second windows?** Short enough to react within a cycle, long enough to have a meaningful sample of requests. *(Confirm this was your reasoning.)*
5. **How did you know it worked?** The per-shard rate is published as a metric, so you can watch each shard's limit adapt. [From memory, if you recall: was the one-hour pause still happening for enabled tenants?]
6. **What if your mentee had got stuck?** [From memory: one real moment]
7. **How do you pick work for a mentee?** Real stakes, a clear contract (here: per-shard deletes, adaptive, no pauses), and a reviewer who won't take the keyboard.
8. **Who else did you mentor? Your resume says 4+.** Two closely at Oracle (this story, plus the junior on Java 17 / pagination / Uber metrics), and three-plus at Nutanix (S11). [Make sure the "4+" adds up in your own head]

### Weak spots & risks
- **Ownership wording.** "I designed it, they built it" is a *strength* here. Don't drift into "I built".
- The design doc isn't in your folder. Be ready to **whiteboard the controller** (window, two thresholds, ×1.2 / ×0.8, floor and ceiling, per namespace-shard key) from memory.
- The idle-shard catch was yours (you confirmed). Tell it the way it actually happened: as a question you asked, or a flaw you pointed out.

**Sources:**
- OLM git history (`olmgit/casper-lifecycle-engine`):
  - CASPER-48919 / CASPER-48918 and "changes for rate limiting" (2025-03-07)
  - "change rate limit adjustment logic" (2025-04-09, diff read)
  - `RateLimiterController.java`, `base.conf` `rateLimiterConfiguration`
- `Batch Operation MDS Improvement/Batch Operation MDS Improvement_…pdf` (one-hour pause), `Batch Delete ECAR_…pdf` (OLM to adjust for more 429s)
- Your answers of 2026-11-01 (designed it; mentee built; SD1 → SD2; reviews with questions)

---

## S10 · SQL Server on Windows Storage Spaces (Nutanix): growing database storage without risking consistency

**Hook:** Enterprise customers moving off SAN wanted many databases under one mount point on Windows Storage Spaces. I owned provisioning there, and found disks couldn't be grown in place without risking database consistency, so I designed growth by adding balanced sets of disks.

| | |
|---|---|
| **Amazon LPs** | Primary: **Customer Obsession**, **Invent and Simplify** · Secondary: Dive Deep, Ownership, Deliver Results |
| **Google attributes** | Comfort with ambiguity · Putting the user first · Storage durability thinking |
| **Tilt** | **Google ★★★** (storage, consistency, capacity: a different system from Oracle, which helps with "another example") · Amazon ★★ |

### Situation & Task (~20%)
- Nutanix **NDB/Era** automates database lifecycle (provision, backup, clone) for enterprise SQL Server. 🟢
- Customers migrating from **SAN** wanted multiple databases under a single mount point. **Windows Storage Spaces** does that by pooling disks into virtual disks, like software RAID. 🟢
- It was a **critical ask for RBL Bank, Zillow and Temenos** (provisioning), and storage extension was requested by **Softbank Technology, RBL and Servus Credit Union**. 🟢
- **My task:** I had **full ownership** of provisioning on Storage Spaces and Dynamic Disks, plus the **auto-extension / extend-storage** feature. 🟢 (2023 resume)

### Action (~60%)
1. **Provisioning on Storage Spaces** (supported from Era 2.1): create the pool, the virtual disk and the volume, and make registration, app-consistent snapshots, log snapshots and cloning work on it. 🟢
2. **Tested the obvious extend approach first, and it failed.** 🟢
   - I tried growing the existing disks in the pool. They **can't be extended inline**: a disk must be removed and re-attached to the pool.
   - That disk already hosts database files, so removing it would leave the **database inconsistent**.
3. **Designed growth by adding disks.** 🟢
   - The only safe way to grow the pool is to **add new physical disks**.
   - **How many** and **what size** come from config (`sql_template.yml`), independent of vCPU count, so performance stays balanced across the pool.
   - I walked through the cases (e.g., 8 × 500 GB data pool at 3.8 of 3.9 TB used) in the design.
4. **Handled unlimited max size and alerting.** 🟢 Logic for when a pool needs extending, how to report metrics for storage-space databases with unlimited max size, and when to raise space alerts.
5. **Found a race in parallel provisioning.** 🟢 (extend-during-provision design)
   - With three parallel provisions on one pool, the space check could run **before or after** another provision's extension.
   - Without serialization, two provisions could both decide there's room, or both extend.
   - I proposed a **lock around the space check** with a **10% buffer**, and compared two approaches.
6. Built a POC first (`ShivangExtendDiskPOC` branch). 🟢 [From memory: year (2021–22?), which Era release shipped it, and your role in the Temenos app-consistent restore]

### Result + learning
- 🟢 Storage Spaces provisioning shipped (supported from Era 2.1). Extending storage-space databases followed (supported by 2.4), and I then designed extend-during-provisioning on top.
- [From memory: adoption: did RBL / Zillow / Temenos go live on it? Any escalation it resolved?]
- **Learning:** with storage, **try the obvious operation on a real system before designing**. The "just grow the disk" assumption would have put customer databases at risk.

### Spoken script (2.5–3 min)
> At Nutanix, I worked on NDB, our database-as-a-service product for enterprise SQL Server. / Customers moving off SAN storage wanted many databases under one mount point, / and on Windows the way to do that is **Storage Spaces**: / pool a set of disks, carve virtual disks out of the pool. / Banks like RBL, and companies like Zillow and Temenos, needed it. / I had full ownership of provisioning on Storage Spaces, and later of extending that storage.
>
> Provisioning was the first part: / building the pool and volumes, / and making snapshots, log backups and cloning all work on top.
>
> The interesting problem was **growth**. / Databases fill up, / and customers need to extend storage. / The obvious design is to just grow the disks in the pool. / So I tried that, on a real setup, / and **it doesn't work inline**. / You have to remove the disk from the pool and re-attach it, / and that disk is holding live database files. / Removing it would leave the **database inconsistent**.
>
> So the only safe way is to **add new disks** to the pool. / The design question became how many and what size, / so performance stays balanced. / I made that config-driven, / so it's predictable and doesn't depend on the VM's CPU count, / and I worked through the edge cases, / like a pool at 3.8 of 3.9 terabytes.
>
> Later, extending storage during provisioning raised a **race**: / three databases provisioning in parallel on one pool, / each checking free space, / one of them extending in the middle. / Without serialization, two could both think there's room. / So I put a lock around the space check with a ten percent buffer, / and compared two ways to sequence it.
>
> Provisioning on Storage Spaces shipped in Era 2.1, / and extending it followed by 2.4.
>
> The lesson I still use: / with storage, try the obvious operation on a real system before you design. / The "just grow the disk" assumption would have put customer data at risk.

### 60-second version
> At Nutanix, I owned SQL Server provisioning on Windows Storage Spaces, / a critical ask from customers like RBL Bank, Zillow and Temenos moving off SAN. / The hard part was growth. / I tested growing the pool's disks in place, / and found you must remove and re-attach the disk, / which would leave a live **database inconsistent**. / So I designed growth by **adding balanced sets of new disks**, config-driven, / and later caught a **race** in parallel provisioning on one pool, / fixed with a lock around the space check and a 10% buffer. / It shipped in Era 2.1, with extension following by 2.4.

### Likely follow-ups
1. **Why can't you extend a disk in a Storage Spaces pool?** The disk has to be removed and re-added to the pool to use new capacity. With database files on it, removal breaks consistency.
2. **Why config-driven disk count rather than tying it to vCPUs?** Predictability: the number and size of disks added come from the template, so behaviour doesn't change by VM size. [From memory: any performance reasoning you used]
3. **How did you test consistency?** [From memory]
4. **What about AG / multi-cluster setups?** The extension use cases covered standalone, clone, AG and multi-cluster AG databases. [From memory: which you implemented]
5. **What was the race exactly?** Parallel provisions checking free space before vs after another's extension. Fix: serialize the space check with a lock, plus a 10% buffer.
6. **What did RBL actually need?** [From memory]

### Weak spots & risks
- **Outcome missing.** Even "RBL went live" is enough.
- Dates are fuzzy (around Era 2.1–2.4). Know roughly when.

**Sources:**
- `Ntnx TechNotes/NTNX technotes/MSSQL - Storage space support_…pdf`
- `…/160998185_…pdf` (extend on Storage Spaces; "Why we can not simply extend…")
- `…/Extend underlying storage space _…pdf` (parallel-provision race)
- `…/Database Storage Extension_…pdf` (customer asks)
- `Shivang_resume_nutanix_2023.pdf` ("full ownership… RBL bank, Zillow, Temenos")
- `Shivang_Badola_Resume.pdf`

---

## S11 · SQL Server test automation + training (Nutanix)

**Hook:** Our SQL Server driver had thin automated coverage. I built **~80–90 functional tests** for single-instance and Availability-Group databases, and ran training sessions so the team could extend them.

| | |
|---|---|
| **Amazon LPs** | Primary: **Insist on the Highest Standards**, **Hire and Develop the Best** · Secondary: Ownership, Frugality |
| **Google attributes** | Collaboration · Growth mindset (for the team) · Leading without authority |
| **Tilt** | **Amazon ★★★** (mentoring backup + raising the bar) · Google ★★ |

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

### Likely follow-ups
1. **Why VDI-based tests?** [From memory]
2. **What did the tests catch?** [From memory]
3. **How did you get people to attend and adopt?** [From memory]
4. **What did you mentor the "3+ developers" on?** [From memory]
5. **How did you prioritize which tests to write first?** [From memory]
6. **What happened to the framework after you left?** [From memory]

### Weak spots & risks
- Thin on results. Fine as a **backup** mentoring story, not a lead.

**Sources:** `Ntnx TechNotes/NTNX technotes/236192748_…pdf` (weekly status, Jan–Mar 2023), `Shivang_resume_nutanix_2023.pdf`, `Shivang_Badola_Resume.pdf`

---

## S12 · Least-privilege Active Directory for SQL Server AGs (Nutanix)

**Hook:** Our AG setup needed the cluster to have **full control over an entire AD OU**, which customers' security teams pushed back on. I moved to **object-level rights** on pre-staged listener objects, plus gMSA support.

| | |
|---|---|
| **Amazon LPs** | Primary: **Success and Scale Bring Broad Responsibility**, **Earn Trust** · Secondary: Customer Obsession, Insist on the Highest Standards |
| **Google attributes** | **Doing the right thing** · Putting the user first |
| **Tilt** | Both ★★. Good answer to "a time you chose the harder, safer path". |

### Situation & Task (~20%)
- Creating a SQL Server Availability Group listener needs AD objects. The simple approach gave the cluster's computer object (CNO) **OU-level full control**, so the cluster could create anything in that OU. 🟢
- **Customers had security concerns** about granting that. 🟢 [From memory: which customers, and was it blocking deals?]
- **Task:** I implemented AD access-control features, including **gMSA** support and **object-level permissions for the AG listener's virtual computer object (VCO)**. 🟢 (resume)

### Action (~60%)
1. **Pre-staged the listener VCO** with **object-level rights** for the CNO, instead of OU-level full control, so the cluster can manage only the one object it needs. 🟢
2. **Added gMSA support** for SQL Server service accounts, so passwords are managed by AD instead of being static secrets. 🟢
3. [From memory: what was hard, e.g., the workflow ordering of pre-staging vs cluster creation, permission propagation delays, customer docs?]

### Result + learning
- 🟢 Removed the need for broad OU-level permissions.
- [From memory: adoption, or a customer it unblocked]
- **Learning:** when customers push back on permissions, they're usually right. Design for the **least privilege that works**, even if it costs more workflow steps.

### Spoken script (~2 min)
> At Nutanix, setting up SQL Server Availability Groups / required giving the Windows cluster **full control over an entire Active Directory OU**, / so it could create the listener object. / Customers' security teams pushed back, / and they were right: / that's far more access than the job needs.
>
> I changed the design so we **pre-stage the listener's computer object** / and grant the cluster rights on **just that object**. / I also added **gMSA** support, / so SQL Server service accounts use AD-managed passwords instead of static ones.
>
> [From memory: what was hard + result.]
>
> What I took from it: / when customers push back on permissions, they're usually right. / Least privilege that works is worth extra workflow steps.

### 60-second version
> Our AG setup needed the cluster to have full control over a whole AD OU, / and customers' security teams objected. / I redesigned it to **pre-stage the listener object with object-level rights only**, / and added gMSA support so service accounts use AD-managed passwords. / [From memory: result.] / Least privilege that works beats convenient access.

### Likely follow-ups
1. **What's a CNO / VCO?** The cluster name object, and the virtual computer object for the AG listener, both in AD.
2. **Why not just document the OU permission?** It puts the security cost on the customer. Many enterprises won't grant OU-wide full control.
3. **What broke when you tightened permissions?** [From memory]
4. **How did you test it?** [From memory]
5. **Why gMSA?** Automatic password rotation and no static service-account passwords.
6. **Which customers asked?** [From memory]

### Weak spots & risks
- Small and early. A backup story for "doing the right thing" / "Success and Scale".

**Sources:** `Ntnx TechNotes/NTNX technotes/72003850_…pdf`, `…/GMSA support for SQL Service log_…pdf`, `Shivang_Badola_Resume.pdf`

---

## S13 · "Your design won't extend": feedback on my Storage Spaces design, applied to restore (Nutanix)

**Hook:** I designed SQL Server provisioning for Windows Storage Spaces, the layout our priority customers wanted. Senior and staff engineers told me it wouldn't extend to Dynamic Disks, which other customers also wanted, and that an escalation would force a risky refactor. It changed how I start every design, and I used it on the next big feature: restore for standalone and AG databases.

| | |
|---|---|
| **Amazon LPs** | Primary: **Earn Trust** (receiving feedback), **Learn and Be Curious** · Secondary: Insist on the Highest Standards, Think Big |
| **Google attributes** | **Growth mindset** · Intellectual humility · Design judgement |
| **Tilt** | Both ★★★ once your honest first reaction is filled in (the last open slot). Fills gap **G2**. |

### Background: Storage Spaces vs Dynamic Disks (for you; say only the short version unless asked)
**Why customers wanted either one.** On SAN, DBAs were used to putting many databases on one big drive or mount point. On Nutanix each virtual disk is separate, so you need a way to **combine several disks into one volume**. Striping across disks also spreads I/O. Era's best-practice config striped **8 data disks (1,000 GB each) and 8 log disks (250 GB each)** into one volume each. 🟢 (`MSSQL - Storage space support…pdf`, BPG config)

| | **Dynamic Disks** (older) | **Storage Spaces** (newer) |
|---|---|---|
| What it is | Windows' original volume manager (Logical Disk Manager). You convert normal ("basic") disks to dynamic, then build volumes across them | Storage virtualization: **pool** the physical disks, carve **virtual disks** ("spaces") out of the pool, then create volumes on them |
| Layouts | Simple, spanned (concatenated), striped, mirrored, RAID-5 volumes | Simple (striped, no redundancy), mirror (2- or 3-way), parity. Thin or fixed provisioning |
| Metadata | An LDM database copy on **every** dynamic disk (last 1 MB on MBR, a hidden 1 MB partition on GPT) | Pool metadata written on **every** member disk. Once pooled, a disk can't join another pool |
| Growing | Only simple and spanned volumes can be extended | Add physical disks to the pool, then grow the virtual disk. In Era, existing disks couldn't be grown in place (S10) |
| Tooling | Disk Management / diskpart (LDM + Virtual Disk Service) | PowerShell storage cmdlets (`New-StoragePool`, `New-VirtualDisk`) |
| Microsoft's status | **Deprecated**, except for mirrored boot volumes | The **recommended replacement** for resilient pooled storage |
| How VSS snapshots see it (Era's finding) | Looks like a normal Nutanix disk (vendor NUTANIX, product VDISK, SCSI bus) | Looks like a Microsoft virtual device (vendor Msft, product "Storage Space", file-backed virtual bus), so the app-consistent snapshot path needed separate work |
| Cloning onto the same host (Era's finding) | Not covered in your docs | Pool metadata on cloned disks collides: disk-signature collision, pool shows degraded or "unrecognized metadata" |

**Why one design didn't cover both.** They differ at **every stage of the lifecycle**: create, find later (Era kept the Dynamic Disks set's mount point in its metadata; for Storage Spaces, saved vs live lookup was an open question), enable per server (Storage Spaces had a per-DB-server mapping, Dynamic Disks was all-or-nothing), grow, snapshot, clone/restore. A design hard-coded to one layout has to be touched at every stage to add the other. That's exactly the feedback. 🟢 (design doc: open questions 3–4, VDS_LUN_INFORMATION table; restore doc: clone experiments)

**Loose analogy for Linux-minded interviewers:** Dynamic Disks ≈ classic software RAID / LVM volumes across disks; Storage Spaces ≈ a pool-first model like LVM thin pools or a ZFS pool. *(Analogy only; don't push it.)*

**Say this if they need context (~20 s):**
> Quick context: customers coming off SAN wanted many databases on one big volume, and Windows has two built-in ways to build a volume across several disks. **Dynamic Disks** is the older one: it stitches disks into spanned or striped volumes, and Microsoft has since deprecated it. **Storage Spaces** is the newer one: you pool the disks and carve virtual disks out of the pool, with options like mirroring and thin provisioning. Same goal, but different tooling, metadata and snapshot behaviour, so a design built around one doesn't automatically work for the other.

**If asked "why was supporting both hard?" (~20 s):**
> They differ at every step: how you create the volume, how you find it later, how you grow it, and how snapshots see it. VSS sees a Storage Spaces virtual disk as a Microsoft virtual device, while a dynamic disk still looks like our own disk. So unless the layout-specific parts are isolated, adding the second layout means touching all of them.

Sources: [Microsoft Learn: Basic and Dynamic Disks](https://learn.microsoft.com/en-us/windows/win32/fileio/basic-and-dynamic-disks) (LDM database location, volume types, extendable volumes, deprecation note) · [Microsoft Learn: Storage Spaces overview](https://learn.microsoft.com/en-us/windows-server/storage/storage-spaces/overview) (pools, virtual disks, simple/mirror/parity, thin provisioning) · your Era design docs (BPG config, VSS table, open questions, clone experiments).

### Situation & Task (~20%)
- ~2021, Nutanix NDB/Era, SQL Server. **I owned provisioning on Windows Storage Spaces and Dynamic Disks**, a critical ask for enterprise customers including a bank. 🟢 (2023 resume)
- Customers moving off SAN wanted many databases under one mount point. Windows offers two ways: **Storage Spaces** (newer, pooled disks, like software RAID) and **Dynamic Disks** (older). 🟢 (design doc: "Storage Spaces and Dynamic disks gives the opportunity…")
- The priority customers needed Storage Spaces. Some customers wanted Dynamic Disks too, and management wanted both supported. 🟢 (your answer of 2026-11-03)
- **Task:** design Storage Spaces provisioning for the priority customers. I designed for Storage Spaces only. 🟢 (your answer)

### Action (~60%)
1. **The feedback.** In review, senior and staff engineers said the design **wouldn't extend to Dynamic Disks**. If a Dynamic Disks customer escalated, I'd have to rework and refactor provisioning code, under pressure, in the path that creates customer databases. Their advice: **make it extensible from the start.** 🟢 (your answer)
   - The design doc shows where the two paths diverged: Storage Spaces had its own enable flag and a **per-DB-server mapping** that Dynamic Disks didn't, and the two found the mount point differently (saved metadata vs live query). The doc even carries the note *"This has to be handled for dynamic disks as well."* 🟢 (`MSSQL - Storage space support…pdf`, provisioning section + open questions 3 and 4)
2. **My reaction.** `[NEED: your honest first reaction, e.g. "I'd scoped it to the customer who mattered most, and this felt like extra work for a maybe". Why it stung: deadline? pride in the design?]`
3. **What I realised.** It wasn't hypothetical. Dynamic Disks was already on management's list and customers were asking. A seam at the known divergence points was cheap now. Retrofitting it during an escalation would be expensive and risky. 🔵 (reasoning from your answer + the doc)
4. **What I changed in that design.** I **isolated the layout-specific steps** (creating the volume, finding it later, growing it, how snapshots/VSS see it) from the common provisioning flow, so a second layout would mean implementing those steps, not reworking the flow. 🟢 (your answer of 2026-11-03: "we had designed in such a way that our existing design works for dynamic disks")
5. **What I changed in how I design.** Before designing, I list the requirements I already know are coming, and I check the design doesn't block any of them. I don't build them. I just don't paint myself into a corner. 🟢 (your answer, paraphrased)
6. **Applied on the next big feature: restore on Storage Spaces.** 🟡→🟢 once confirmed (`156152223_…pdf`; you said you designed it)
   - P0 ask from a customer running Always On **availability groups**, but restore also had to cover **standalone** databases, and AG came in **four shapes**: single or multi-cluster, disks shared or not.
   - I designed **standalone restore as one self-contained flow with its own rollback**: crash-consistent snapshot for rollback → drop DB → delete pool → clone snapshot → bring pool up → apply logs → recover.
   - **AG restore became an orchestrator around that same flow:** run it on the primary, then add only the AG steps (native backup to a temp disk, snapshot, clone to secondaries, native restore, add back to the AG). **Multi-cluster** added one step (replicate the snapshot). **Shared disks** swapped in a copy-based path through a restore proxy VM.
   - The doc lists "reusability of code… stable code path" as a reason for the chosen approach. 🟢

### Result + learning
- 🟢 The restore design covers standalone plus four AG configurations, with dev tests marked done for standalone and single-cluster AG (vdisk and volume group). `[NEED: what shipped, in which Era release; did multi-cluster come later as an add-on?]`
- 🟢 **The Dynamic Disks requirement came back a few months after Storage Spaces support went live**, from customers still on Dynamic Disks who hadn't migrated. It did touch provisioning (the layouts differ at every step), but only in the layout-specific pieces. VSS handling, tests and snapshots were **faster to build and ship** because the design already accommodated it and the team had worked through those areas once. It went in smoothly, and **one system served both** Storage Spaces and Dynamic Disks customers. (your answer of 2026-11-03) No time numbers: don't invent any.
- **Learning:** *design for the requirements you can already see coming, not every one you can imagine.*

### Spoken script: one flow, context → feedback → learning (~3 min)
> At Nutanix, I worked on NDB, our database-as-a-service product, and I owned SQL Server provisioning. A lot of our enterprise customers were moving off SAN storage, where they were used to putting many databases on one big drive. On Nutanix every virtual disk is separate, so we had to combine several disks into one volume.
>
> Windows has two built-in ways to do that. **Dynamic Disks** is the older one: it stitches disks together into spanned or striped volumes, and Microsoft has since deprecated it. **Storage Spaces** is the newer one: you pool the disks and carve virtual disks out of the pool, a bit like software RAID. Same goal, but the tooling, the on-disk metadata, even how snapshots see the disks, are all different. Our priority customers needed Storage Spaces, so that's what I designed for.
>
> In the design review, senior and staff engineers gave me feedback I didn't enjoy hearing. The design worked for Storage Spaces, but it **wouldn't extend to Dynamic Disks**. Some customers wanted Dynamic Disks too, and management wanted both. If one of those customers escalated, I'd be reworking provisioning code under pressure, in the path that creates customer databases. Their advice was simple: **make it extensible from the start.**
>
> `[Your honest reaction, one sentence. E.g. "My first reaction was that I'd scoped it to the customer who mattered most, and this felt like extra work for a maybe." Only if true.]` But when I thought it through, they were right, and not because extensibility is always good. Dynamic Disks wasn't hypothetical; it was already on the list. And I knew exactly where the two layouts differed: how a server gets set up, how we find the volume later, how we grow it, how snapshots work. A seam at those points was cheap now. Retrofitting it during an escalation would be expensive and risky. So I isolated the layout-specific steps from the common provisioning flow.
>
> And it paid off. A few months after Storage Spaces went live, customers still on Dynamic Disks asked for the same support. We still had to write the Dynamic Disks version of each layout-specific step, but we didn't have to rework the flow around them. And because we'd already worked through snapshots, VSS and testing once, it went in quickly and smoothly. From then on, **one system served both**.
>
> The bigger change was in how I start a design. **Before I design anything, I list the requirements I already know are coming, and I check that my design doesn't block any of them.** I don't build them. I just make sure I'm not painting myself into a corner.
>
> The next big feature tested that: restoring SQL Server databases on Storage Spaces. The top-priority ask came from a customer running availability groups, but restore also had to work for standalone databases, and availability groups came in several shapes: single or multi-cluster, disks shared or not. So I designed **standalone restore as one self-contained flow with its own rollback**, and made **availability-group restore an orchestrator around it**: run that same flow on the primary, then add only the group-specific steps, seeding the secondaries and adding them back. Multi-cluster added one more step on top. Each new shape was an addition, not a rewrite.
>
> So the lesson I took: **design for the requirements you can already see coming, not every one you can imagine.** That feedback was uncomfortable at the time, but it's how I've started designs ever since.

- **Timing:** ~3 min. If the interviewer is clearly a Windows/storage person, cut paragraph 2 to one sentence ("Dynamic Disks, the older volume manager, and Storage Spaces, the newer pooled model").
- **Fill the two slots before using it.** Without the honest reaction, it sounds like a routine review comment.
- 🟢 Sources: as in Background and Action above (design doc, restore doc, Microsoft Learn, your answer of 2026-11-03).

### 60-second version
> At Nutanix I designed SQL Server provisioning on Windows Storage Spaces, which our priority customers needed. / Senior engineers told me in review that it **wouldn't extend to Dynamic Disks**, the older option other customers and management also wanted, / so an escalation would mean refactoring risky provisioning code under pressure. / `[Reaction.]` They were right: Dynamic Disks was already on the list, and a seam was cheap now. / So I isolated the layout-specific steps, and when Dynamic Disks support was requested a few months later, **it went in as an addition, not a rework.** / Since then, **I list the requirements I know are coming and make sure the design doesn't block them.** / On the next feature, restore, I built standalone restore as a self-contained flow and made AG restore an orchestrator around it, / so each AG configuration was an addition, not a rewrite.

### Likely follow-ups
1. **"Isn't that over-engineering? What about YAGNI?"** Yes, if it's for requirements you imagine. I only leave a seam when there's evidence the requirement is coming (it's on the roadmap, customers are asking) **and** retrofitting later would mean touching risky code under pressure. A seam isn't a feature: it costs an interface, not a second implementation.
2. **"What exactly did you change after the feedback?"** `[NEED]` (Action 4).
3. **"Why was it hard to hear?"** `[NEED]` (Action 2). Something like "I'd optimised for the deadline and the priority customer, and it meant redoing work I thought was done", if true.
4. **"How did you respond in the review?"** `[NEED]` Strong shape, only if true: asked which scenarios worried them, took it offline, came back with the revised design.
5. **"Did Dynamic Disks ever come back?"** Yes, a few months after Storage Spaces went live. See follow-up 8.
6. **"Walk me through the AG restore flow."** Remove from AG → restore on primary (with rollback) → native backup on a temp disk → snapshot → clone to secondaries → native restore with no recovery → add back to the AG. If a secondary fails, the primary and the healthy secondaries stay in the AG and the user gets an alert. 🟢 (restore design docs)
7. **"Have you used this at Oracle?"** Closest: on versioned metrics I picked the simple approach but documented where it stops and what replaces it (S1). Keep it to one line if S1 or S6 follow-up 15 was already told.
8. **"What was the measurable impact? Did it save time or reduce risk when Dynamic Disks was built out?"** (~60 s) *Branch A is true (your answer of 2026-11-03). No time numbers exist; don't invent any.*
   > Yes, it came back. A few months after Storage Spaces support went live, customers who were still on Dynamic Disks, and hadn't moved, asked for the same support. It did mean writing code in provisioning, because the two layouts differ at every step: how you create the volume, how you find it later, how you grow it, and how snapshots see it. But because I'd isolated exactly those steps, **adding Dynamic Disks meant writing the Dynamic Disks version of each one, not reworking the flow around them.** The rest, the VSS snapshot handling, the tests, the snapshot workflow, we'd already worked through once for Storage Spaces, so it was much faster to build and ship. I don't have a precise before-and-after in weeks, and I won't make one up. But it went in smoothly, and from then on **one system served both groups**: customers on Storage Spaces and customers still on Dynamic Disks. That was exactly the scenario the senior engineers had warned me about, and it turned into a routine feature instead of a rework.
   - 🟢 Your answer of 2026-11-03. The "differ at every step" detail is backed by the design doc (VDS_LUN_INFORMATION table; open questions 3–4).
   - **If pushed for a number:** *"I didn't track it, and time you didn't spend is hard to measure. The clearest signal is that it was an addition: the common flow stayed, and Storage Spaces customers weren't disrupted."* `[Confirm: Storage Spaces customers weren't disrupted]`
   - **Restore as a second proof point** (if they ask for more): two core paths (disk swap; file copy for shared disks), each reused across standalone, single-cluster AG and multi-cluster AG: six configurations from two flows. 🔵 (my count from the restore doc)
   - **Don't:** claim it didn't touch provisioning at all, a number of weeks saved, or "zero bugs".
9. **"Did it have any impact on your team? Did others pick it up, or did it change how the team made similar decisions?"** (~70 s) 🟢 (your answer of 2026-11-03)
   > Yes, it did. We were building the product more or less from scratch, and enterprise customers kept coming in with requests that were variants of things we'd already built: another storage layout, another database topology. After this, the way we approached a new feature changed. Before committing to a design, we'd ask **which variants customers were likely to ask for next**, and make sure the design wouldn't block them. Not building them up front, just leaving room. So when one of those requests did come in, **we could commit to it with confidence**, because the code was ready to be extended rather than rewritten.
   >
   > It also changed me as a reviewer. Whenever I reviewed a design for a new feature on the team, I'd look for exactly that: *this could be extended in this direction, and if a customer asks for it, here's what it would take.* It became a habit I brought to every review, not something I had to remind myself of. `[One real example: "On a teammate's design for X, that question surfaced Y, and we Z."]`
   - **Expect "give me an example".** Have one real review in mind: whose feature, what variant you spotted, what changed in the design. Without it, the second paragraph sounds generic. `[NEED]`
   - **Keep the filter in your wording:** "variants customers were *likely* to ask for", not "everything that could come". That keeps it clear of the YAGNI objection (follow-up 1).
   - **If asked "how do you know the team changed?":** say how it showed up (the question being asked in design reviews, designs leaving room for the next variant). Only cite a design-doc section or checklist if one really existed.
   - **Optional extra team impact (different topic, say so):** the SQL Server functional-test automation (~80–90 tests across standalone and AG) and the training sessions teammates relied on. 🟢 (S11)
10. **"How has this habit changed the way you mentor or onboard newer engineers?"** (~80 s) *Built from real S9/S11 material, nothing invented. It survives follow-ups because git and the promotion back it up.*
    > It shows up in how I explain designs and how I review. When I hand work to someone newer, I don't just hand over the ticket. I walk them through **why the design looks the way it does, including what's likely to come next.**
    >
    > The clearest example is at Oracle. I designed per-shard rate limiting for our lifecycle engine and handed the build to an SD1 engineer I was mentoring. Part of the "why" was that a change on the metadata side was about to throttle the lifecycle engine *more*, so the design had to handle the throttling we knew was coming, not just what we had that day. `[Confirm: you explained this to them]` It's also why it was switched on per tenant through config: we knew we'd want to roll it out gradually.
    >
    > In reviews, I ask questions instead of writing fixes, and they're the same kind of question the senior engineers asked me: **what happens in the case you haven't seen yet?** With my mentee it was: "what happens to the limit on a shard that gets no traffic for a window?" They found the flaw themselves and fixed it. It shipped, and **they were promoted to SD2** with it as their main work.
    >
    > So the habit I try to pass on isn't "make everything extensible". It's: **before you design, ask what's already coming; before you ship, ask what case you haven't tested.**
    - 🟢 S9: Embargo redesign "was going to send OLM more 429s" (situation); enabled per tenant in config; idle-shard review question; ×1.2/×0.8 adaptive limiter; mentee SD1 → SD2 in Aug 2025. Implementation is your mentee's (CASPER-48918/48919): say "I designed it, they built it."
    - **Optional Nutanix line (onboarding):** *"At Nutanix, I built our SQL Server test automation, about 80–90 tests across standalone and availability-group databases, and ran the training sessions teammates used to get up to speed on it."* 🟢 (S11) Say "teammates", not "new hires", unless they were.
    - **Story reuse:** if S9 was already told in this loop, compress the middle to "the rate-limiting work I mentioned, where I handed my mentee the build".
    - **Don't add:** a mentoring scene, a "design checklist I gave juniors", or a number of mentees you can't name.

### Weak spots & risks
- **"Hard to hear" is mild for design-review feedback.** It only lands with an honest first reaction (Action 2). Without it, it sounds like a routine review comment.
- **What existed for Dynamic Disks before?** Your account: full Dynamic Disks support came a few months after Storage Spaces went live. The Storage Spaces design doc already mentions some Dynamic Disks behaviour ("in dynamic disk support, user can either choose dynamic disk set or normal disks"). If asked, be ready to say what existed before `[NEED, low priority: e.g. partial or older support?]` so you don't get tripped by "wasn't that already supported?"
- **Restore ownership:** the restore design doc names approvers, not an author (🟡). You've said you designed it, so be ready to explain the orchestrator flow from memory (follow-up 6).
- **"If AG came tomorrow":** in the doc, AG restore is P0 alongside standalone, not a later add-on. Say "restore had to cover standalone and every AG shape", not "AG might come later", unless AG really did ship later.
- **Same project as S10.** Don't tell both in one loop unless asked for another example.
- **No names:** "senior and staff engineers", "a key customer". Don't name reviewers or customers.

**Sources:**
- `Ntnx TechNotes/NTNX technotes/MSSQL - Storage space support_…pdf` (why, config flags, per-DB-server mapping, Dynamic Disks notes and open questions)
- `…/156152223_…pdf` (Storage Space app-consistent restore: standalone + four AG configurations, rollback, AG orchestrator, reuse rationale, test table)
- `…/Restore SQL Server AG Database_…pdf` (AG restore flow and negative scenarios)
- `Shivang_resume_nutanix_2023.pdf` (ownership of provisioning on Storage Spaces and Dynamic Disks)
- your answer of 2026-11-03 (the feedback, who gave it, and applying it to restore)

---

## S14 · Explaining the 8-week trade-off to our TPM (versioned metrics)

**Hook:** For the versioned-metrics feature, I needed our TPM behind the less obvious design, query-time aggregation instead of the textbook summary table, with an 8-week deadline. I explained it in their currency: time, risk, and who gets hurt if we're wrong.

| | |
|---|---|
| **Amazon LPs** | Primary: **Earn Trust**, **Customer Obsession** · Secondary: Deliver Results, Frugality |
| **Google attributes** | **Communication with non-specialists** · User focus · Pragmatism |
| **Tilt** | Both ★★★ for "explain to a non-technical audience and get support" (gap **G11**). **Same project as S1:** if S1 is told in the loop, use this only as its communication angle. |

### Situation & Task (~20%)
- A strategic customer moving onto OCI Object Storage, with **~700 buckets**, had no metrics for versioned objects, so they couldn't see what old versions cost them. I owned the feature and had **8 weeks**. 🟢 (S1; your answers)
- Two ways to build it (🟢 HLD appendix):
  - **Summary table:** keep a pre-aggregated count, updated on every write. Fast to read, but it changes the write, delete and versioning flows, needs a backfill and extensive validation, and takes longer.
  - **Query-time aggregation:** a separate daily job that counts from existing data. No change to the write path. Fits the deadline, but it's a batch job with a scale ceiling.
- **Audience:** our TPM, tracking the schedule and the customer commitment, not database internals. `[Confirm the TPM's role]` 🟢 (your answer of 2026-11-03: you explained the trade-off to the TPM)
- **Task:** explain the trade-off so the TPM could back the approach and the plan.

### Action (~60%)
1. **Started from what the TPM cared about:** the date, the risk, and the customer. Not tables and indexes. 🟢 (your answer)
2. **One picture for each option.** 🔵 (analogy; use it only if it's how you explained it, or present it as "the way I'd put it")
   - Summary table = **a running tally at every checkout counter**: always current, but you have to change every counter, and here the counter is the code every customer's upload goes through.
   - Query-time aggregation = **counting the inventory once a day in the back room**: touches nothing customers use; it just takes a while to count.
3. **Compared them in the TPM's terms.** 🟢 (HLD pros/cons, S1 follow-up 9)
   | | Running tally (summary table) | Daily count (query-time) |
   |---|---|---|
   | Fits 8 weeks? | No: write-path change + backfill + validation | Yes |
   | Who's at risk if it's wrong? | **Every customer's uploads** | One customer's daily number is late or missing |
   | What we give up | Time | Real-time freshness; a scale ceiling |
4. **Was upfront about the downsides.** 🟢 (S1)
   - Daily, not real-time.
   - **Fail closed:** if we can't trust a bucket's number, we skip it rather than publish a wrong one.
   - **A documented ceiling:** about 2–3 minutes for ~700 buckets; over 20 minutes at ~10K buckets on one database. Beyond that, the summary table is the way to go.
5. **Checked understanding.** `[NEED: how. E.g. the TPM's questions, or you asked them to restate the trade-off for the customer]`
6. **The ask.** `[NEED: what support you asked for and got. E.g. sign-off on the approach, help with the telemetry dependency (TEL-23840), setting the customer's expectation of a daily metric]`

### Result + learning
- 🟢 Shipped **inside the 8 weeks**, with **no change to the write path**; the customer could see version count and version storage per bucket for the first time, and was happy. (S1; your answer)
- `[NEED: what the TPM did with it, e.g. carried it to the customer, held the date]`
- **Learning:** *explain trade-offs in the other person's currency (time, risk, and who gets hurt if you're wrong), not in yours.*

### Spoken script (~2.5 min)
> For a strategic customer moving onto our object storage, I owned a new feature: metrics for versioned objects. They had about seven hundred buckets and no way to see what their old versions were costing them, and I had **eight weeks**.
>
> There were two ways to build it, and I needed our TPM, who was tracking the schedule and the customer commitment, to back the less obvious one. So I didn't start with databases. I started with what they cared about: **the date, the risk, and the customer.**
>
> I explained the options with a picture. Option one is like keeping **a running tally at every checkout counter**: every sale updates it, so it's always current and fast to read. But you have to change every checkout counter, and here the checkout counter is the code every customer's upload goes through. Option two is like **counting the inventory once a day in the back room**. It doesn't touch anything customers use; it just takes a while to count.
>
> Then I put them side by side in their terms. The tally is the right long-term answer at huge scale, but it meant changing the most critical path in the system, backfilling existing data, and a lot more validation. Not realistic in eight weeks, and if we got it wrong, **every customer's uploads were at risk**. The daily count fit the deadline, and if we got it wrong, the worst case was **one customer's daily number arriving late**.
>
> I was upfront about what we'd give up. The numbers would be daily, not real-time. If we couldn't trust a bucket's number, we'd skip it rather than publish a wrong one. And it had a ceiling: by my estimate, ten thousand buckets on one database would take over twenty minutes, so I wrote down that beyond that point, the tally is the way to go.
>
> `[How you checked they understood, one sentence.]` `[The support you asked for and got, one sentence.]`
>
> We shipped inside the eight weeks, without touching the write path, and the customer could finally see their version counts and storage.
>
> What I took from it: **explain trade-offs in the other person's currency, time, risk, and who gets hurt if you're wrong, not in yours.**

### 60-second version
> I had eight weeks to ship versioned-object metrics for a strategic customer, and I needed our TPM to back the less obvious design. / I explained it in their terms: a **running tally at every checkout counter** versus **counting the inventory once a day**. / The tally meant changing the code every customer's upload goes through, plus a backfill: no way in eight weeks, and a bug would hit **every customer**. / The daily count touched nothing customers use; worst case, **one customer's daily number arrives late**. / I was upfront about the costs: daily not real-time, skip rather than guess, and a documented scale ceiling. / `[Support you got.]` / We shipped inside the eight weeks with no write-path change.

### Likely follow-ups
1. **"How did you know the TPM really understood?"** `[NEED]` Strong shape, only if true: they restated it to the customer or in the plan in their own words.
2. **"What if the TPM had pushed for the 'proper' solution?"** I'd have shown the timeline for it honestly (write-path change, backfill, validation) and let them choose with the risk on the table, but I'd have argued for the daily count for this customer.
3. **"Did the customer accept daily numbers?"** `[NEED]` They were happy with the result (your answer). Don't claim a specific conversation you weren't in.
4. **"What did you leave out of the explanation?"** Sharding, fan-out, Oracle hints, the 8× GROUP BY tuning. None of it changed the decision for the TPM.

### Weak spots & risks
- **Same project as S1 (and S5).** Don't tell S14 and S1 as separate stories in one loop.
- **A TPM is semi-technical.** Say "our TPM, who owned the schedule rather than the database details", so the interviewer accepts the "non-technical" framing.
- **The analogy is mine** unless you used it. If you explained it differently, use your own picture.
- **No names:** "a strategic customer", "our TPM". 

**Sources:** S1 (HLD appendix pros/cons, estimates, fail-closed, 8 weeks, outcome); your answer of 2026-11-03 (explained the trade-off to the TPM under the 8-week deadline).

---

## S15 · "Nothing changed, so why is it slow?": explaining index fragmentation to our TPM

**Hook:** Queries slowed down for a customer even though we hadn't shipped anything. I had to explain to our TPM that the database had degraded on its own because index maintenance had been paused for months, and get support for the fix.

| | |
|---|---|
| **Amazon LPs** | Primary: **Earn Trust**, **Dive Deep** · Secondary: Customer Obsession, Ownership |
| **Google attributes** | **Communication with non-specialists** · Problem solving · Humility (no blame) |
| **Tilt** | ★★★ once the TPM's part is filled in (outcome confirmed). Backup for G11. **Overlaps S2/S6** (fragmentation) and S1 (if it was the metrics queries). |

### Situation & Task (~20%)
- In IAD and PHX, **index rebuilds had been paused for a couple of months**, so some database shards were **heavily fragmented**. 🟢 (your answers of 2026-11-02/03)
- **The versioned-metrics job's per-shard queries ran very slowly** for the strategic customer's buckets. 🟢 (your answer of 2026-11-02: challenge 2 of the versioned-metrics launch)
- Our TPM's question: **why is it slow when we haven't changed anything recently?** 🟢 (your answer)
- **Task:** explain the real cause in plain terms and get support for `[NEED: what you needed: a manual rebuild in a constrained region, DBPerf time, a revised date, customer communication]`.

### Action (~60%)
1. **Investigated with DBPerf** and traced the slowness to heavily fragmented indexes on those shards. 🟢 (your answer)
2. **Reframed "nothing changed":** *the code didn't change; the data did.* Customers delete objects every day, and with cleanup paused, the indexes fill up with dead entries that every query still walks past. 🟢 (mechanism: rebuild docs; S6 follow-up 11)
3. **One picture:** 🔵 (analogy; use your own if you used a different one)
   - **A library where removed books leave their shelf slots reserved.** Normally a crew slides books together. In those two regions, the crew had been stopped for months, so every search walked past empty shelves.
4. **Explained why "just turn it back on" wasn't instant.** The cleanup had been paused for a reason: the full rebuild itself had caused incidents in exactly those regions. So the fix was a **targeted manual rebuild** of the affected indexes, with DBPerf. 🟢 (ORR: rebuilds paused due to impact; your answer: manual rebuild)
5. **The ask and the plan.** `[NEED: what you asked the TPM for and what they did]`
6. `[NEED, optional: what you showed: e.g. bytes per row on the affected partitions vs the ideal of 200, or query time before/after. Only real values]`

### Result + learning
- 🟢 **Most of the work was diagnosis:** going through diagnostic logs to find exactly which shards had queries timing out. All of them were **heavily fragmented**. 🟢 **Targeted manual rebuilds** on just those shards, with DBPerf, took **about half a day**. Afterwards **query execution time came back down** and the service was **back up with correct results**. (your answer of 2026-11-03)
- 🟢 **Rough numbers:** the query timeout (which you set) was **10 minutes**; on the worst shards the query was taking **more than an hour**; after the rebuild it finished **well under 10 minutes**, and the timeouts stopped. 🔵 That's at least **6× faster** in the worst cases (>60 min → <10 min), and from never finishing to finishing every run.
- **Learning (communication):** *when someone says "nothing changed", look for what changed without a deploy: the data, the load, and the maintenance that stopped. Then explain it with one picture and a plan.*
- **Link, if asked:** this is the cost of paused maintenance that Index Shrink (S2/S6) was built to reduce. Don't say shrink fixed it unless it did.

### Spoken script (~2.5 min)
> After we'd launched a feature for a strategic customer, some of its queries started running very slowly `[what was slow, in customer terms]`. Our TPM asked a fair question: **we haven't changed anything recently, so why is it slow?**
>
> I dug in with our database performance team, and the answer was that the code hadn't changed, but **the data had**. In our two biggest regions, index maintenance had been paused for a couple of months, after the maintenance itself had caused incidents there. Meanwhile customers kept deleting objects every day.
>
> So I explained it with a picture. Think of a library where, when a book is removed, its slot on the shelf stays reserved. Normally a crew comes round and slides the books together. In those two regions, **the crew had been stopped for months**, so every search was walking past more and more empty shelves. Nothing was broken; it was just getting slower every day.
>
> The obvious question was "so turn the crew back on". I explained why it wasn't that simple: the full cleanup was paused because it had caused incidents in exactly those regions. So the plan was a **targeted manual rebuild** of the indexes this feature depended on, done with the database performance team. `[What you asked the TPM for, and what they did.]`
>
> Most of the work was finding exactly where the problem was. Going through the diagnostic logs, we found the shards whose queries were timing out, and every one of them was heavily fragmented, too far gone for a lighter fix. So we rebuilt just those, which took about half a day. Afterwards, queries that had been taking **over an hour against a ten-minute timeout finished well inside it**, and the service was back up with correct results.
>
> What I took from it: **when someone says nothing changed, look for what changed without a deploy: the data, the load, and the maintenance that stopped.** And explain it with one picture and a plan, not a lecture on indexes.

### 60-second version
> A customer's queries slowed down although we hadn't shipped anything, and our TPM asked why. / With our DB performance team, I found the cause: **the code hadn't changed, the data had.** Index maintenance had been paused for months in our two biggest regions, so dead entries from daily deletes piled up. / I explained it as **a library where removed books leave empty slots, and the crew that tidies the shelves had been stopped**. / And why we couldn't just restart it: the full cleanup had caused incidents there. / So we found the shards that were timing out from the diagnostic logs and rebuilt just those with DBPerf: about half a day, and queries that had taken **over an hour finished well under the ten-minute timeout**. `[TPM's part.]`

### Likely follow-ups
1. **"Why was maintenance paused?"** Online rebuilds had caused incidents in those regions (10 auto-cuts, 11 Sev2s in 2–3 months). 🟢 (S2)
2. **"How did you prove it was fragmentation?"** The diagnostic logs showed which shards had queries timing out, and those shards were heavily fragmented. 🟢 (your answer) `[NEED, optional: the measure, e.g. bytes per row vs the ideal of 200]`
3. **"Couldn't you have used your Index Shrink feature?"** Not for these. They were heavily fragmented, and at that level shrink helps much less; our own design sends those partitions to a full rebuild instead. 🟢 (your answer of 2026-11-03: "maybe shrink would not have helped"; ORR "Limitations" and the >300 bytes-per-row rule) Say "much less effective at that level", not "shrink can't do it".
4. **"What did the TPM do with your explanation?"** `[NEED]`
5. **"Who was in the room or on the thread: just the TPM, or product, leadership, the customer?"** (~40 s) *Your files and answers only confirm the TPM and DBPerf. Don't add anyone else unless they were there.*
   > Mainly the TPM. They owned the customer commitment, so they were the right person to understand it and carry it forward. Our database performance team was in the investigation, and with them the conversation was technical: which indexes, how fragmented, what the rebuild would cost. With the TPM it was the picture and the plan. `[Only if true: My manager was copied, because a manual rebuild in those regions needed their OK.]` I wasn't talking to the customer directly; `[Only if true: the TPM took it to them, using the same explanation.]`
   - 🟢 TPM and DBPerf (your answers of 2026-11-02/03). Everything bracketed needs confirming.
   - **Why the honest answer is fine:** a small audience isn't a weakness. "The person who owned the customer commitment" shows you picked the right audience. Tailoring the same facts for DBPerf and for the TPM shows communication range.
   - **Don't add:** product, a director or a customer call you weren't on. A follow-up like "what did the customer say?" will expose it.
6. **"How exactly did you structure the explanation: a written doc, something drawn live on a call, something else?"** (~60 s) *The medium isn't in your files. Pick the opening that's true; the four-part structure is the same either way.*
   - **Opening, pick one:** `[It was a call, and I followed it with a short written summary they could forward]` · `[It was on a Slack thread, so I wrote it in four short parts]` · `[I wrote a short note before we spoke]`
   > Either way, the structure was the same: four parts, in this order.
   >
   > **First, the answer in one line:** the code didn't change, the data did. Index maintenance had been paused in those regions, so the indexes had filled up with dead entries from everyday deletes.
   >
   > **Second, one picture:** the library where removed books leave their slots reserved, and the crew that tidies the shelves had been stopped. I kept the internals out of it. I wanted one image they could repeat to someone else.
   >
   > **Third, why the obvious fix wasn't safe:** the cleanup had been paused because it caused incidents in exactly those regions, so we couldn't just switch it back on everywhere.
   >
   > **Fourth, the plan and what I needed:** a targeted manual rebuild of the indexes this feature depended on, with the database performance team, `[rough timeline]`, and `[what you needed from the TPM]`.
   >
   > Answer first, then the picture, then the risk, then the plan. If they only read the first line, they still had the right answer.
   - 🟢 Content of each part: S15 Action (your answers of 2026-11-02/03; ORR for why rebuilds were paused). `[NEED]` the medium, the timeline and the ask.
   - **Don't add** a diagram, a doc title or a meeting you don't remember. "A short written summary" is only true if you sent one.
7. **"What was the concrete outcome? Did the TPM approve it, how long did it take, did it fix the customer's queries?"** (~60 s) 🟢 (your answer of 2026-11-03)
   > `[TPM: "The TPM backed the plan" / "It was an operational call with DBPerf, and the TPM kept the customer informed". Pick what's true.]` The rebuild itself took **about half a day**. Most of the work came before that: going through the diagnostic logs to find exactly which shards had queries timing out, instead of rebuilding everything in those regions. Every one of those shards turned out to be **heavily fragmented**. That's also why my own Index Shrink feature wasn't the right tool here: at that level of fragmentation shrink helps much less, and our design sends those partitions to a full rebuild.
   >
   > So we did **targeted manual rebuilds on just those shards**, with the database performance team. Afterwards, **query execution times came back down, and the service was back up, producing correct results.**
   >
   > What I'd highlight is the targeting. By narrowing it to the shards that were actually timing out, we kept a heavy operation small, in regions where rebuilds had caused incidents before.
   - **If pushed for numbers:** *"I don't have the exact before-and-after. The clear signal was that the timeouts stopped and the results were correct again."*
   - **Don't add:** a percentage improvement, a shard count or an approval meeting you don't remember.
8. **"Any rough numbers: how much did latency drop, what did the timeout rate look like before vs after?"** (~40 s) 🟢 (your answer of 2026-11-03)
   > Rough numbers, yes. The service ran these queries with a **ten-minute timeout**, which I'd set. On the worst shards, the same query was taking **more than an hour**, so it could never finish inside the timeout, and those shards kept timing out. After the targeted rebuild, the same queries finished **well under ten minutes**, comfortably inside the timeout, and the timeouts on those shards stopped. So in the worst cases that's **at least six times faster**. More importantly, it took them from never finishing to finishing every run.
   - 🔵 "At least 6×" is a lower bound (>60 min → <10 min). Don't say "10×" or a percentage unless you remember one.
   - ⚠️ **Expect: "If the timeout was ten minutes, how did you know it took over an hour?"** `[NEED: e.g. you or DBPerf ran it manually without the timeout, or it showed in the database's session/SQL monitoring]`
   - **Timeout rate:** you don't have a percentage. "Those shards timed out every run before; none did after" only if that's accurate. Otherwise "the timeouts stopped".
   - `[Optional, only if this was the versioned-metrics job: "Because the job fails closed, a timed-out shard meant its buckets were skipped for that day rather than published wrong. That's what the customer would have noticed."]`
9. **"Beyond 'look for what changed without a deploy', what would you do differently: investigation, communication, prevention?"** (~75 s) *Not the "baseline metrics" lesson (S1/S2/S7 already use it).*
   > Three things, one in each area.
   >
   > **Investigation:** most of the time went into reading diagnostic logs to work out which shards were timing out. Next time, the service publishes **query time and timeouts per shard from day one**, so the slow shards show up on a dashboard in minutes instead of being dug out of logs.
   >
   > **Communication:** honestly, I should have seen it coming. I knew rebuilds were paused in those regions; I'd worked on that problem myself. And I still didn't connect it to my own feature's queries. The readiness review for that launch listed no risks. Next time, a known weak dependency like that goes in as a **launch risk**, so the TPM hears about it from me before the customer feels it.
   >
   > **Prevention:** treat **index health as a dependency of the feature**. We already had a measure of how bloated each partition is, bytes per row. I'd alarm on it for the indexes my queries rely on, so we catch fragmentation before queries hit the timeout. More broadly, a paused maintenance job needs a tripwire, an alarm and a date to revisit, so a reasonable pause can't quietly stretch into months.
   - 🟢 Diagnosis by log trawling (your answer of 2026-11-03). `[Confirm: there was no per-shard query-time metric or alarm]`
   - 🟢 Versioned-metrics ORR: "Risks: N/A". You knew about the IAD/PHX pause from S2/S6. Rebuilds paused "for a couple of months" (your answer).
   - 🟢 bytesPerRow is the rebuild/shrink signal (rebuild docs; shrink metric `mds.rebalancer.index.shrink.bytes.per.row`).
   - **Don't** claim the pause had no alarm or review date. You don't know that. Keep the tripwire point general ("a paused job needs…").
   - **Overlap:** S1 follow-up 12 makes the same "Risks: N/A" and index-health points. Don't use both in one loop.

### Weak spots & risks
- **Overlaps S2/S6 and S1.** In one loop, don't tell S15 alongside S2/S6. If S1 was told, S15 can be its post-launch chapter.
- **The "support" part is thin until filled.** The question asks how you got their support. Without the ask (step 5), it's an explanation story, not a persuasion story.
- **Don't blame the managers who paused maintenance.** It was a reasonable call; say so.

**Sources:** your answers of 2026-11-02/03 (fragmented IAD/PHX shards, paused rebuilds, DBPerf, manual rebuild, explaining to the TPM); rebuild docs and ORR for the mechanism and why rebuilds were paused (S6 follow-up 11, S2).

---

## S16 · Fitting a SQL Server snapshot into Windows' 10-second window (Nutanix)

**Hook:** Almost everything Era does (backup, restore, point-in-time recovery, clone, provisioning from a backup) starts from an application-consistent snapshot. On Windows, VSS gives the storage snapshot **at most 10 seconds** while every write to the volume is held, and the customer's production database can't write during that time. I optimised our snapshot path so the Nutanix snapshot finished inside that window. `[NEED: one result phrase]`

| | |
|---|---|
| **Amazon LPs** | Primary: **Dive Deep**, **Insist on the Highest Standards** · Secondary: Customer Obsession, Deliver Results |
| **Google attributes** | Technical depth / problem solving (not a core Googleyness story; use it for "hardest technical problem") |
| **Tilt** | Amazon ★★★ once Action and Result are filled in. Google ★★. A Nutanix **Dive Deep** story that balances an Oracle-heavy loop. |
| **Status** | 🟡 **Skeleton.** The constraint and stakes are verified; what broke, what you changed and the result are `[NEED]` |

### Background: VSS in 60 seconds (say only the short version unless asked)
**What it is.** The Volume Shadow Copy Service is Windows' framework for taking a consistent snapshot ("shadow copy") of data while the application keeps running. It coordinates four parts: 🟢 (Microsoft Learn, VSS overview)

| Part | What it does | In this story |
|---|---|---|
| **VSS service** | Part of Windows; makes the other three talk to each other in the right order | Windows |
| **Requester** | The software that asks for the snapshot, usually the backup application | Era's snapshot workflow `[NEED: confirm Era's agent on the DB server was the requester]` |
| **Writer** | The application's component that puts its data in a consistent state and freezes its writes | SQL Server's **SQL Writer** service (it talks to SQL Server through VDI) 🟢 |
| **Provider** | The component that actually creates the snapshot. A **hardware provider** hands the work to the storage system | The Nutanix-side snapshot `[NEED: was it a Nutanix VSS hardware provider, or Era calling the Nutanix snapshot API while writes were frozen?]` |

**The sequence, and where the 10 seconds come from** 🟢 (Microsoft Learn: VSS overview; SQL Writer guide)
1. The requester asks VSS to prepare; each writer describes what it needs backed up.
2. Writers prepare (SQL Server finishes open work and flushes).
3. **Freeze:** the SQL Writer asks SQL Server to freeze I/O on each database in the snapshot. Reads still work; **writes wait**. The writer freeze may last **at most 60 seconds**.
4. VSS flushes and freezes the file system.
5. **Commit:** the provider creates the snapshot. This step gets **at most 10 seconds**, and **all write I/O to the file system stays frozen** throughout.
6. VSS releases file-system writes, then tells writers to **thaw**.
7. If writers stay frozen for more than 60 s, or the provider takes more than 10 s, **the snapshot is aborted**. The call fails with a timeout error (e.g. `VSS_E_HOLD_WRITES_TIMEOUT`). Microsoft's guidance is to **wait ten minutes and retry, up to three times**.

**Correction to your framing:** the 10 seconds isn't SQL Server's rule; it's **VSS's limit on the provider's commit**. SQL Server's freeze can last up to 60 seconds. Say: *"Windows gives the storage snapshot at most ten seconds, while it holds every write to the volume."*

**Free evidence for the window:** SQL Server writes "I/O is frozen on database…" and "I/O was resumed on database…" to its error log, so every snapshot leaves its own start and end timestamps. 🟢 (IBM APAR IT14926 quotes these messages) `[Use only if you actually used them]`

**Why it mattered**
- **Customers felt it directly:** while the window is open, writes to their production database wait. A slow commit means their application stalls. 🟢 (Microsoft Learn)
- **The whole product depends on snapshots:** restore, point-in-time recovery (a snapshot plus log catch-up), clones, provisioning from a backup, and restore from a remote snapshot all start from one. 🟢 (your account; technotes: "ERA 2.4 – Provision from backup", "Restore from a remote snapshot", "SQL Server Crash Consistent Snapshots in Era 2.0")
- **A missed window costs a restore point:** the snapshot is aborted, and the documented retry is ten minutes later. 🟢 (Microsoft) `[NEED: what Era did when a snapshot failed: retry, mark the snapshot failed, alert?]`
- **The escape hatch was worse:** Era later offered **crash-consistent snapshots** (no VSS) as a server-wide config. With them, **point-in-time restore and point-in-time clones aren't supported**. So app-consistent snapshots had to work. 🟢 (technote) `[NEED: was that config before or after your fix?]`

### Situation & Task (~20%)
- Nutanix NDB/Era, SQL Server driver team. `[NEED: year / Era version]`. Your resume: backup and restore of SQL Server using **VSS and VDI**, implemented in **C++**. 🟢 (2023 resume)
- Snapshots were P0 for the product; every Time Machine operation depends on them. 🟢 (your account)
- **The problem:** `[NEED: what you saw. Snapshots failing with a VSS timeout? At a customer, or in QA? On which configurations: many disks (the best-practice layout was 8 data + 8 log disks), many databases per instance, Storage Spaces?]`
- **Task:** make the Nutanix-side snapshot finish **reliably inside the 10-second window**. 🟢 (your account) `[NEED: was it assigned to you, or did you pick it up? Solo or with others?]`

### Action (~60%)
1. **Measure the window.** `[NEED: how you saw where the 10 seconds went: timestamps around each step between freeze and thaw? the SQL error-log freeze/resume lines? logs on the Nutanix side?]`
2. **Find what was eating it.** `[NEED: the culprit(s)]`
3. **Fix it.** `[NEED: what you changed. Tick from the menu below or describe it]`
4. **Prove it.** `[NEED: how you tested: the largest disk counts, many databases, under write load?]`

**Menu: common ways to fit work inside a VSS window. These are not facts about your work; keep only what you actually did.**

| Technique | What it means | Did you? |
|---|---|---|
| Move prep out of the window | Look up the VM and its disk IDs, authenticate, and open the API connection **before** the freeze, so the window holds only the snapshot call | ? |
| One snapshot call for all disks | Snapshot every data and log disk in one consistency-group call instead of one call per disk | ? |
| Snapshot only what's needed | Put only the database's volumes in the snapshot set (hardware providers snapshot whole LUNs) | ? |
| Do follow-up work after the thaw | Return as soon as the point-in-time copy exists; register metadata, replicate, etc. after writes resume | ? |
| Fewer databases per freeze | For very large instances, split databases into several snapshot sets | ? |
| Handle timeouts explicitly | Detect a VSS timeout, retry, and surface it instead of failing silently | ? |

### Result + learning
- `[NEED: before/after: "the commit went from about X s to about Y s"; did timeouts stop; which release; which customer types benefited]`. If you have no numbers, say what was true, e.g. "snapshots stopped timing out on [those configurations]". Only if it's true.
- **Learning** 🔵 (a suggested framing; use it only if it matches what you did): *"When a platform gives you a hard time budget, treat it like a critical section: only the work that must happen while writes are held goes inside, and everything else moves before or after. And measure the window before you optimise it."*

### Spoken script (~2.5 min), with slots
> At Nutanix I worked on NDB, our database-as-a-service product, on the SQL Server side. / Almost everything the product does starts from a **snapshot** of the customer's database: / backups, restores, point-in-time recovery, cloning a copy for test, provisioning a new database from a backup. / So snapshots were P0 for us.
>
> For SQL Server, a usable snapshot has to be application-consistent, and on Windows that goes through **VSS**, the Volume Shadow Copy Service. / It coordinates three parties: / the **requester**, the backup software asking for a snapshot; / the **writer**, SQL Server's own component that gets the database consistent and freezes its writes; / and the **provider**, which actually takes the snapshot, in our case on Nutanix storage.
>
> The catch is timing. / Windows holds every write to the volume while the provider takes the snapshot, and gives it **at most ten seconds**. / Miss that, and Windows aborts the snapshot. / And while you're inside that window, **the customer's production database can't write**.
>
> `[What went wrong, e.g. "We started seeing snapshots time out on larger configurations."]` / I took on making our snapshot path fit that window reliably.
>
> First, I measured it. `[How, e.g. "I timestamped every step between the freeze and the thaw."]` / That showed `[what was eating the time]`.
>
> `[What you changed: one to three concrete changes. If it fits: "I treated those ten seconds like a critical section. Only the snapshot call itself stayed inside; everything else moved before the freeze or after the thaw."]`
>
> `[How you proved it: the largest configurations, many databases, under load.]`
>
> `[Result, e.g. "The commit went from about X seconds to about Y, and the timeouts stopped."]`
>
> What I took from it: / when a platform hands you a hard time budget, don't try to make everything faster. / Find out exactly what's inside the window, / and move everything that doesn't need to be there out of it.

- **Fill the four slots before using it.** Without them, it's a description of VSS, not a story about you.
- **Calibrate the VSS explanation to the interviewer.** For a Windows or storage person, paragraph 2 becomes one sentence.

### 60-second version
> At Nutanix, almost everything our database service did (backup, restore, clones, provisioning from a backup) started from an application-consistent snapshot of the customer's SQL Server database. / On Windows that goes through VSS, which holds every write to the volume while the storage snapshot is taken, and gives it **at most ten seconds**, or the snapshot is aborted. / `[What went wrong.]` / I measured where the ten seconds went, `[what you found]`, and `[what you changed]`. / `[Result.]` / The lesson: with a hard time budget, find out exactly what's inside the window, and move everything that doesn't have to be there out of it.

### Likely follow-ups
1. **"Why not just take a storage snapshot? Why VSS at all?"** A plain storage snapshot is only **crash-consistent**: like pulling the power cord, recoverable but with no guarantee about in-flight work. VSS makes it **application-consistent**, which point-in-time restore and clones depend on. Era did later offer crash-consistent snapshots as a config, but without PITR or point-in-time clones. 🟢
2. **"Where does the 10-second limit come from?"** VSS itself: the provider must commit within 10 seconds while file-system writes are held. Writers can stay frozen for up to 60 seconds. It isn't configurable. 🟢 (Microsoft)
3. **"What happens if you miss it?"** VSS aborts the shadow copy; the call returns a timeout error; the guidance is to retry after ten minutes. Meanwhile, the customer's writes were stalled for the whole attempt. 🟢 + `[NEED: what Era did]`
4. **"How did you know where the time went?"** `[NEED]`
5. **"What exactly did you write, and in what language?"** Your resume says C++ for VSS/VDI backup and restore. `[NEED: which component you wrote: requester, provider glue, the snapshot workflow?]`
6. **"What's the difference between VDI and VSS?"** VDI is SQL Server's own backup API, for streaming backups to and from a backup application. VSS is Windows' snapshot coordination framework. SQL Server's VSS writer uses VDI internally to talk to SQL Server. 🟢 (Microsoft SQL Writer guide)
7. **"Does it get worse with more disks or more databases?"** `[NEED: what you saw]`. Only say "more disks made it worse" if you observed it.
8. **"What would you do differently?"** `[NEED]`. One honest option, if true: put snapshot commit time on a dashboard from day one, so the window's headroom is visible before customers hit the limit. (Don't repeat the "baseline numbers" line already used in S1/S2/S7.)

### Weak spots & risks
- **Action and Result are empty.** This is the most important gap. Don't use the story until slots 1–4 are filled. An interviewer will ask "what exactly did you change?" within 30 seconds.
- **Your exact role in the VSS chain.** Be ready to say what Era owned (requester? provider?) and what Windows or SQL Server did. Getting this wrong in front of a Windows-savvy interviewer costs credibility.
- **Same competency as S7.** Both are Dive Deep or "hardest technical problem". Use one per loop. S16 is the Nutanix option.
- **No customer names.** Say "an enterprise customer".
- **Don't add events.** No invented customer escalation, outage or deadline. If a real one happened, it makes the story much stronger: tell me and I'll add it.

**Sources:**
- [Microsoft Learn: Volume Shadow Copy Service](https://learn.microsoft.com/en-us/windows-server/storage/file-server/volume-shadow-copy-service) (components, sequence, 60 s writer freeze, 10 s provider commit, abort, LUN-level hardware snapshots)
- [Microsoft Learn: IVssBackupComponents::DoSnapshotSet](https://learn.microsoft.com/en-us/windows/win32/api/vsbackup/nf-vsbackup-ivssbackupcomponents-dosnapshotset) (hold/flush-writes timeout errors; retry after ten minutes, up to three times)
- [Microsoft Learn: SQL Writer backup guide](https://learn.microsoft.com/en-us/sql/relational-databases/backup-restore/sql-server-vss-writer-backup-guide) (freeze all database I/O; snapshot phase under 60 s; SQL Writer uses VDI)
- [IBM APAR IT14926](https://www.ibm.com/support/pages/apar/IT14926) (SQL Server "I/O is frozen" / "I/O was resumed" messages)
- `Ntnx TechNotes/NTNX technotes/SQL Server Crash Consistent Snap…pdf` (crash-consistent config; no PITR); technote titles for provision from backup and remote-snapshot restore
- `Shivang_resume_nutanix_2023.pdf` (VSS, VDI, C++ for backup and restore)
- your account of 2026-11-04 (snapshots are P0; the 10-second window; optimising the Nutanix-side snapshot)

---

## S17 · Soft Delete in OLM: making the one irreversible step impossible to take early

**Hook:** In Object Storage, a delete used to be permanent. Even with versioning, anyone with enough permissions (or ransomware with stolen credentials) could destroy a specific version for good. Soft Delete keeps deleted data recoverable for a window the customer sets. `[CONFIRM: I designed and built]` the lifecycle engine's side: the background processor that **permanently purges** data once that window expires. In a feature built to make deletes safe, the purge is the one step you can't undo.

| | |
|---|---|
| **Amazon LPs** | Primary: **Customer Obsession**, **Insist on the Highest Standards** · Secondary: Success and Scale Bring Broad Responsibility, Ownership, Dive Deep |
| **Google attributes** | **User first / Doing the right thing** · Required category: **reliability / data integrity** |
| **Google tie-in** | Cloud Storage has the same feature: soft delete is on by default for supported buckets, with a 7-day default retention (configurable 7–90 days). 🟢 (Google Cloud docs) |
| **Tilt** | Google ★★★ (data protection is a core Cloud Storage concern) · Amazon ★★ |
| **Status** | 🟡 **Ownership and ship status unconfirmed.** See the evidence check first |

### Evidence check (read before using)
- **Your resume:** "Added Soft Delete capability to OLM: deleted data is first kept in a recoverable state for a customer-defined retention period, then permanently purged by a new background processor once that period expires." 🟡 (your claim)
- **Your folder:**
  - The OLM HLD, the OLM LLD (marked **UNDER-REVIEW**) and the cross-team design doc. None names an author. The files are dated **5 Dec 2025**.
  - In the cross-team doc's task table:
    - MDS schema: **DONE**.
    - MDS APIs: **IN PROGRESS** (targets 21 Nov – 23 Dec).
    - The three OLM tasks (cache 0.5 wk, processor 1.5 wk, testing 3 wk): **NOT STARTED**.
- **Your OLM git copy ends Aug 2025**, so it can't confirm either way.
- **Before using this, confirm:**
  - (a) you wrote the OLM HLD and LLD;
  - (b) you built the processor;
  - (c) whether it shipped before you left.
- **If it didn't ship,** tell it as a design story ("I designed it; it was in testing when I left") and soften the resume verb from "Added" to "Designed".

### Background: the feature in 30 seconds 🟢 (cross-team design doc)
- **Before:**
  - Deleting a non-versioned object is permanent.
  - Versioning keeps old versions, but "a user with sufficient permissions can still permanently delete a versioned object".
- **Soft Delete configuration:**
  - A bucket-level setting with three states: **Disabled** (the default), **Enabled**, **Suspended**.
  - Retention is **1–365 days, default 7**.
  - Config changes take effect only after a **cool-off** (default **24 h**, 1–240 h), so a malicious insider can't switch protection off instantly.
- **MDS side** (the metadata team's design; don't claim it):
  - A deleted version moves to a **separate table**, stamped with `soft_deletion_time` and `soft_deletion_expiry_time`.
  - Normal GET, HEAD and LIST calls don't see it. Only admins with a new permission can list or restore it.
- **Retention changes apply only to objects deleted after the cool-off.**
- **Soft-deleted versions are billed** at their storage class, and **a bucket can't be deleted** while it still holds soft-deleted objects.
- **OLM's role** (OLM HLD): lifecycle becomes two steps.
  - **User rules** now soft-delete instead of deleting.
  - **Auto-created system rules** hard-delete once the retention has passed.

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

### Likely follow-ups
1. **"Why not just rely on versioning?"** Versioning keeps old versions, but anyone with delete-version permission can still remove one permanently. Soft Delete adds a window that even they can't skip, plus a cool-off on config changes. 🟢
2. **"Why a separate table instead of a soft-delete flag?"** The metadata team's choice, so credit them. The doc weighs three options:
   - **Separate table** (chosen): live-object queries stay fast; purging hits one table; less risk of leaking deleted data into normal listings. Cost: moving rows between tables, and schema duplication.
   - **Flag column:** index and table bloat; every query needs a filter.
   - **Name prefix:** expensive renames; fragile restore. 🟢
3. **"What if a customer lowers retention from 30 days to 1?"** Already-deleted versions keep their stamped expiry. The new value applies only to objects deleted after the 24-hour cool-off. 🟢
4. **"How do you avoid scanning the whole fleet?"** Cache only the buckets that have or had soft delete; list per bucket and shard, in pages. 🟢
5. **"What if OLM falls behind?"** That's the safe direction: data is kept longer, not lost. It costs the customer storage, so the design adds delay metrics and alarms. The LLD's future scope lists a tenant-specific rate limiter for soft-delete purges. 🟢 `[Link to S9 only if you designed that too]`
6. **"Clock skew between OLM and MDS?"** The MDS check is the backstop: it rejects a purge inside the window. `[NEED: anything more you handled]`
7. **"How did you test it?"** The plan: unit, integration, OST canaries, and end-to-end tests including thread-pool tuning. OSTs needed a new clean-up, because buckets holding soft-deleted objects can't be deleted. `[NEED: what you actually ran, and what it caught]`
8. **Google: "We have soft delete in Cloud Storage. How does yours compare?"**
   - **GCS:** on by default; 7-day default retention; range 7–90 days.
   - **This design:** off by default; 1–365 days, default 7; a cool-off before config changes take effect.
   - The same core idea: a recovery window that ordinary delete permissions can't bypass. 🟢

### Weak spots & risks
- **Ownership and ship status** (see the evidence check). As of the Dec 2025 docs, the OLM tasks were "not started". If an interviewer asks "what's the adoption?", you need a true answer.
- **Docs disagree on suspend behaviour.** The OLM HLD says that after soft delete is disabled, existing soft-deleted data stays for **14 days**. The cross-team doc says it stays **until each version's own retention expires**. Know which shipped. Mentioning that you caught it (only if you did) is a good Dive Deep detail.
- **Don't claim the MDS or web-server design** (table, APIs, permissions, cool-off). Say "the metadata team" or "the design".
- **Don't use the AI-written guide** in `STAR Method Projects Discussions/OLM_Soft_Delete_Interview_Guide.docx` as evidence. It's not a source.
- **Same service as S9.** Fine in one loop, since they're different projects, but don't open both with "the lifecycle engine runs customers' rules…".

**Sources:**
- `MDS-OLM Soft deletes/OLM Soft deletes High level design .pdf` (two-step lifecycle, edge-case tables, three states, OLM code flow, 14-day note)
- `MDS-OLM Soft deletes/OLM Soft deletes low level design .pdf` (module responsibilities, has/had cache, processor, thread pools, evaluator, If-Match purge, error table, rollout gating, metrics, future rate limiter, estimates)
- `MDS-OLM Soft deletes/Object Storage - Soft Deletes_…pdf` (problem, requirements, cool-off, retention rules, separate table + alternatives, MDS rejection inside retention, DeleteBucket rule, metering, task table and statuses)
- `Shivang_Badola_Resume.pdf` (the Soft Delete bullet)
- [Google Cloud: Soft delete](https://docs.cloud.google.com/storage/docs/soft-delete) (on by default; 7-day default; 7–90 days)

---

## Open items, by priority

**Batch 4: answered 2026-11-01.** Zero Sev2s from shrink, IAD/PHX enabled · pagination shipped around Mar–Apr (year: confirm 2026) · Java 17: bad latency, rollout held, release slipped for the fix + re-qualification · mentee made SD2 in the Aug 2025 cycle; the idle-shard flaw was yours · Uber happy, 8-week deadline.

**From memory before interviews (no answer needed here)**
- S7: how you narrowed it to TLS, plus one red herring you chased.
- S9: one moment your mentee got stuck and what you did.
- S10: how consistency was tested. S11: what the tests caught.
- S3: client disconnects and backpressure (not in the doc).
