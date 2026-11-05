# 12 · Dive Deep: Java 17 regression

**Lead:** S7 · **Backup:** S16 · **Backup:** S4

**Angle to stress (07):** ~8 weeks to a TLS default; only stopped when the cause explained everything

> Copied on 2026-11-04 from `03_star_stories.md`: hook, STAR points, spoken scripts and 60-second versions only. Follow-ups and weak spots stay in 03. Later edits to 03 won't show up here.

| Story | Role | Status (03 index) | Before you use it |
|---|---|---|---|
| S7 · My Java 17 upgrade caused a performance regression (failure #1) | Lead | 🟢 release slipped | Use only one S7 version per loop (03). |
| S16 · Fitting a SQL Server snapshot into Windows' 10-second window (Nutanix) | Backup | 🟡 skeleton · needs what broke, what you changed, result | Not ready: needs what you changed and the result (07). Fill the slots before using it (03). |
| S4 · DBMS_LOCK Sev2: proving a hash collision and locking it down | Backup | 🟢 your parts · "we shipped" | Backup only: the PR is a teammate's, so say "we shipped" (04). |

---

## Lead · S7 · My Java 17 upgrade caused a performance regression (failure #1)

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

---

## Backup · S16 · Fitting a SQL Server snapshot into Windows' 10-second window (Nutanix)

**Hook:** Almost everything Era does (backup, restore, point-in-time recovery, clone, provisioning from a backup) starts from an application-consistent snapshot. On Windows, VSS gives the storage snapshot **at most 10 seconds** while every write to the volume is held, and the customer's production database can't write during that time. I optimised our snapshot path so the Nutanix snapshot finished inside that window. `[NEED: one result phrase]`

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

---

## Backup · S4 · DBMS_LOCK Sev2: proving a hash collision and locking it down

**Hook:** An internal customer's cluster deletions were blocked because aborting one multipart upload failed on **every** retry. I proved, with a hash POC, that two unrelated lock keys landed on the same Oracle lock ID. I argued for the targeted fix we shipped as a patch, and wrote the regression test that pins the exact collision.

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
