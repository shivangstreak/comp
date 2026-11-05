# 04 · Are Right, A Lot: Wrong Index Shrink rule

**Lead:** S8 · **Backup:** S5

**Angle to stress (07):** My own experiment proved my rule wrong; I changed it

> Copied on 2026-11-04 from `03_star_stories.md`: hook, STAR points, spoken scripts and 60-second versions only. Follow-ups and weak spots stay in 03. Later edits to 03 won't show up here.

| Story | Role | Status (03 index) | Before you use it |
|---|---|---|---|
| S8 · My first Index Shrink rule was wrong (failure #2 / "a time you were wrong") | Lead | 🟢 |  |
| S5 · Disagreeing with the DBPerf expert on batch size (conflict #1) | Backup | 🟢 |  |

**Notes**
- Out loud, say "a critical customer", not the customer's name (06 avoid list).

---

## Lead · S8 · My first Index Shrink rule was wrong (failure #2 / "a time you were wrong")

**Hook:** My first design chose between shrink and rebuild by **partition size**. My own experiment showed same-size partitions needing opposite treatment, and under my rule one of them would have been sent to a rebuild that **failed**.

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

---

## Backup · S5 · Disagreeing with the DBPerf expert on batch size (conflict #1)

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
