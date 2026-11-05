# 05 · Learn and Be Curious: Design feedback Storage Spaces

**Lead:** S13 · **Backup:** S7 · **Backup:** S10

**Angle to stress (07):** Feedback changed how I start every design. S10 if asked "learned a new domain fast"

> Copied on 2026-11-04 from `03_star_stories.md`: hook, STAR points, spoken scripts and 60-second versions only. Follow-ups and weak spots stay in 03. Later edits to 03 won't show up here.

| Story | Role | Status (03 index) | Before you use it |
|---|---|---|---|
| S13 · "Your design won't extend": feedback on my Storage Spaces design, applied to restore (Nutanix) | Lead | 🟢 Dynamic Disks payoff confirmed · needs your first reaction | Needs one sentence (your first reaction) before it leads (07). |
| S7 · My Java 17 upgrade caused a performance regression (failure #1) | Backup | 🟢 release slipped | Use only one S7 version per loop (03). |
| S10 · SQL Server on Windows Storage Spaces (Nutanix): growing database storage without risking consistency | Backup | 🟢 needs outcome |  |

**Notes**
- Out loud, say "a critical customer", not the customer's name (06 avoid list).

---

## Lead · S13 · "Your design won't extend": feedback on my Storage Spaces design, applied to restore (Nutanix)

**Hook:** I designed SQL Server provisioning for Windows Storage Spaces, the layout our priority customers wanted. Senior and staff engineers told me it wouldn't extend to Dynamic Disks, which other customers also wanted, and that an escalation would force a risky refactor. It changed how I start every design, and I used it on the next big feature: restore for standalone and AG databases.

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

---

## Backup · S10 · SQL Server on Windows Storage Spaces (Nutanix): growing database storage without risking consistency

**Hook:** Enterprise customers moving off SAN wanted many databases under one mount point on Windows Storage Spaces. I owned provisioning there, and found disks couldn't be grown in place without risking database consistency, so I designed growth by adding balanced sets of disks.

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
