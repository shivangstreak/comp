# 15 · Strive to be Earth's Best Employer: Mentee to SD2

**Lead:** S9 · **Backup:** S11

**Angle to stress (07):** Found promotion-worthy work for a junior

> Copied on 2026-11-04 from `03_star_stories.md`: hook, STAR points, spoken scripts and 60-second versions only. Follow-ups and weak spots stay in 03. Later edits to 03 won't show up here.

| Story | Role | Status (03 index) | Before you use it |
|---|---|---|---|
| S9 · Designing OLM's per-shard rate limiting and growing my mentee to SD2 through it | Lead | 🟢 (design: you said) |  |
| S11 · SQL Server test automation + training (Nutanix) | Backup | 🟢 needs impact |  |

**Notes**
- ⚠️ Weak LP: S9 is the only real story. From 04 §4: Amazon asks this as "how have you made your team a better place to work / supported someone's growth".
- Out loud, say "a critical customer", not the customer's name (06 avoid list).

---

## Lead · S9 · Designing OLM's per-shard rate limiting and growing my mentee to SD2 through it

**Hook:** My mentee needed high-impact work to move from SD1 to SD2. I designed per-shard adaptive rate limiting for our lifecycle engine, handed them the build, and coached them through it, reviewing with questions instead of fixes. It shipped, and they were promoted.

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

---

## Backup · S11 · SQL Server test automation + training (Nutanix)

**Hook:** Our SQL Server driver had thin automated coverage. I built **~80–90 functional tests** for single-instance and Availability-Group databases, and ran training sessions so the team could extend them.

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
