# 11 · Earn Trust: Re enabling maintenance

**Lead:** S6 · **Backup:** S13 · **Backup:** S14

**Angle to stress (07):** Gave managers controls (allow-list, dry-run, rollback) to say yes

> Copied on 2026-11-04 from `03_star_stories.md`: hook, STAR points, spoken scripts and 60-second versions only. Follow-ups and weak spots stay in 03. Later edits to 03 won't show up here.

| Story | Role | Status (03 index) | Before you use it |
|---|---|---|---|
| S6 · Pushing to turn maintenance back on in the regions managers had paused (conflict #2) | Lead | 🟢 |  |
| S13 · "Your design won't extend": feedback on my Storage Spaces design, applied to restore (Nutanix) | Backup | 🟢 Dynamic Disks payoff confirmed · needs your first reaction | Needs one sentence (your first reaction) before it leads (07). |
| S14 · Explaining the 8-week trade-off to our TPM (versioned metrics) | Backup | 🟡 needs how you checked understanding + the support you got |  |

---

## Lead · S6 · Pushing to turn maintenance back on in the regions managers had paused (conflict #2)

**Hook:** After rebuilds hurt our two biggest regions, managers had paused index maintenance there. I pushed to enable Index Shrink in exactly those regions, because the pause was the problem shrink was built to solve.

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

---

## Backup · S13 · "Your design won't extend": feedback on my Storage Spaces design, applied to restore (Nutanix)

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

## Backup · S14 · Explaining the 8-week trade-off to our TPM (versioned metrics)

**Hook:** For the versioned-metrics feature, I needed our TPM behind the less obvious design, query-time aggregation instead of the textbook summary table, with an 8-week deadline. I explained it in their currency: time, risk, and who gets hurt if we're wrong.

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
