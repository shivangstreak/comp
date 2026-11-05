# 16 · Success and Scale Bring Broad Responsibility: Least privilege AD

**Lead:** S12 · **Backup:** S3 · **Backup:** S17

**Angle to stress (07):** Least privilege over convenience. S3: protecting other tenants

> Copied on 2026-11-04 from `03_star_stories.md`: hook, STAR points, spoken scripts and 60-second versions only. Follow-ups and weak spots stay in 03. Later edits to 03 won't show up here.

| Story | Role | Status (03 index) | Before you use it |
|---|---|---|---|
| S12 · Least-privilege Active Directory for SQL Server AGs (Nutanix) | Lead | 🟢 needs customers |  |
| S3 · Paginated GET: stopping one tenant's huge downloads from hurting everyone | Backup | 🟢 |  |
| S17 · Soft Delete in OLM: making the one irreversible step impossible to take early | Backup | 🟡 ownership + ship status unconfirmed | Not ready: needs your role and ship status (07). If it didn't ship, tell it as a design story: "I designed it; it was in testing when I left" (03 evidence check). |

---

## Lead · S12 · Least-privilege Active Directory for SQL Server AGs (Nutanix)

**Hook:** Our AG setup needed the cluster to have **full control over an entire AD OU**, which customers' security teams pushed back on. I moved to **object-level rights** on pre-staged listener objects, plus gMSA support.

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

---

## Backup · S3 · Paginated GET: stopping one tenant's huge downloads from hurting everyone

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
