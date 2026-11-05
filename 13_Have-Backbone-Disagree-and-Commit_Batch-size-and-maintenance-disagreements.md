# 13 · Have Backbone; Disagree and Commit: Batch size and maintenance disagreements

**Lead (peer):** S5 · **Lead (manager):** S6

**Angle to stress (07):** Disagreed with data, kept it reversible

> Copied on 2026-11-04 from `03_star_stories.md`: hook, STAR points, spoken scripts and 60-second versions only. Follow-ups and weak spots stay in 03. Later edits to 03 won't show up here.

| Story | Role | Status (03 index) | Before you use it |
|---|---|---|---|
| S5 · Disagreeing with the DBPerf expert on batch size (conflict #1) | Lead (peer) | 🟢 |  |
| S6 · Pushing to turn maintenance back on in the regions managers had paused (conflict #2) | Lead (manager) | 🟢 |  |

**Notes**
- ⚠️ No real "lost the argument and committed" story yet. Interviewers often ask for exactly that.
- Out loud, say "a critical customer", not the customer's name (06 avoid list).

---

## Lead (peer) · S5 · Disagreeing with the DBPerf expert on batch size (conflict #1)

**Hook:** I asked our database-performance team how big my query batches should be. Their expert recommended **3–5× bigger** than mine. I kept 15 because of what our cold-run data showed, and we wrote down what would change the decision.

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

---

## Lead (manager) · S6 · Pushing to turn maintenance back on in the regions managers had paused (conflict #2)

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
