# 06 · Hire and Develop the Best: Mentee to SD2

**Lead:** S9 · **Backup:** S11

**Angle to stress (07):** SD1 → SD2; reviews by questions, not fixes

> Copied on 2026-11-04 from `03_star_stories.md`: hook, STAR points, spoken scripts and 60-second versions only. Follow-ups and weak spots stay in 03. Later edits to 03 won't show up here.

| Story | Role | Status (03 index) | Before you use it |
|---|---|---|---|
| S9 · Designing OLM's per-shard rate limiting and growing my mentee to SD2 through it | Lead | 🟢 (design: you said) |  |
| S11 · SQL Server test automation + training (Nutanix) | Backup | 🟢 needs impact |  |

**Notes**
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

---

*Below: your own write-up for this principle, pasted 2026-11-04, unchanged.*

# Amazon Leadership Principle: Hire and Develop the Best

## 1. Interview Script (3–4 minutes)

### Situation

At Oracle, I was working in the OCI Object Storage organization, primarily across the Metadata Service (MDS) and Object Lifecycle Management (OLM) teams.

I was mentoring two junior engineers, and one of them was at the SD1 level. They were looking to make the case for promotion to SD2.

I felt that simply assigning them implementation tasks on my existing projects wouldn't give them the ownership or visibility needed to demonstrate SD2-level impact.

Around that time, I noticed a significant scalability problem in our Object Lifecycle Management engine, or OLM.

OLM executes customer-defined lifecycle policies, such as deleting object versions older than 30 days, by sending delete requests to our metadata database shards.

The problem was that whenever MDS throttled OLM, the lifecycle engine would pause processing that bucket for an entire hour before retrying.

This created a burst-wait-burst pattern. OLM would send a large number of deletes, get throttled, remain idle for an hour, and then resume at full speed, often triggering throttling again.

An upcoming change to our batch-delete rate limiting was also expected to increase throttling, so this was becoming an increasingly important problem.

### Task

I saw this as an opportunity to solve two problems simultaneously.

I wanted to improve OLM's scalability, but I also wanted my mentee to own a meaningful engineering initiative that they could take from design through production.

I decided I would own the architecture and technical direction, while they would own the implementation, testing, and delivery end to end.

### Action

There were three things I focused on.

**1. Designed the architecture around the actual bottleneck.**

I realized that the problem was not necessarily with the entire tenant or bucket. The actual bottleneck was an individual metadata database shard.

A tenant could have data distributed across multiple shards, and multiple tenants could also share a shard.

So instead of having a single rate limiter at the tenant level, I designed an adaptive rate limiter for every tenant-and-shard combination.

The rate limiter would evaluate database feedback every five seconds.

- If we successfully consumed at least 80% of the allocated capacity, we would increase the rate by 20%.
- If at least 20% of requests failed, we would decrease the rate by 20%.
- Otherwise, we would maintain the existing rate.

We also enforced a minimum rate of 100 and a maximum of 10,000 deletes per second.

This meant that if one shard became overloaded, only that shard would slow down. Other healthy shards could continue processing.

We also made the feature configurable per tenant, allowing us to roll it out incrementally.

**2. Deliberately gave my mentee ownership rather than just implementation tasks.**

I walked them through the problem, the reasoning behind choosing shard-level throttling, and the trade-offs involved in the adaptive rate-limiting algorithm.

Once we aligned on the design, they owned the implementation and test suite end to end.

My intention was to give them a problem where they had to exercise independent technical judgment rather than simply translate my design into code.

**3. Focused on coaching through code reviews rather than providing solutions.**

There was one particular instance that stands out.

During a review, I noticed a subtle flaw in their initial rate-limiter implementation.

They were calculating success as the ratio of successful requests to total requests sent.

Consider a shard that had an allowance of 5,000 requests in a five-second window but received only 100 requests.

All 100 requests succeeded.

Their algorithm interpreted that as 100% success and kept increasing the rate, even though the shard had never actually demonstrated that it could handle the higher throughput.

There was another edge case: if a shard received no traffic, it could incorrectly be interpreted as having zero success and have its rate reduced.

Instead of fixing the code myself, I asked them a question:

"What happens to the rate limit of a shard that receives no traffic during a particular window?"

That prompted them to reason through the edge cases themselves.

They eventually changed the calculation to measure successful requests against the allocated allowance, rather than just the requests sent.

This ensured that low traffic wouldn't artificially increase or decrease the rate.

I also reviewed their testing scenarios with them and helped them think through how to communicate the business impact and technical trade-offs of the work for their promotion case.

### Result

The feature was successfully implemented and shipped.

The lifecycle engine no longer needed to pause buckets for an hour whenever an individual shard experienced throttling. Instead, it could adapt the processing rate independently for each shard while allowing healthy shards to continue working.

More importantly, my mentee had delivered a substantial piece of engineering work that they could independently own and defend.

They were promoted from SD1 to SD2 in the next review cycle, and this project became a significant part of their promotion case.

For me, the biggest takeaway was that developing engineers isn't just about giving them guidance or reviewing their code. It's about giving them real problems, meaningful ownership, and enough room to make decisions and learn from them.

I found that asking the right questions during reviews often develops an engineer much more effectively than simply giving them the correct answer.

---

# 2. Potential Amazon Follow-up Questions

## Q1. Why did you choose this particular engineer for the project?

**Suggested answer:**

I considered their existing technical capabilities, their readiness to take on more ownership, and the opportunity to demonstrate skills expected at the next level.

I didn't want to give them a project that was simply larger in terms of coding effort. I wanted something that required design understanding, handling edge cases, testing, and production ownership.

This project provided that opportunity.

## Q2. How did you ensure you weren't micromanaging them?

**Suggested answer:**

I established the architectural direction and clarified the expected outcomes upfront.

After that, I let them own implementation decisions and testing.

During reviews, I focused on asking questions about correctness, scalability, and edge cases rather than prescribing solutions.

I stepped in when architectural guidance was needed, but I deliberately avoided taking over the implementation.

## Q3. What if the engineer couldn't solve the problem?

**Suggested answer:**

I would first try to understand whether they were struggling because of a knowledge gap, an unclear requirement, or an overly broad problem.

I would break down the problem and provide additional context or guidance, but still leave the actual problem-solving to them.

My objective was not to test whether they could solve everything independently from day one. It was to help them develop the judgment to solve increasingly complex problems.

## Q4. How did you know your mentoring was successful?

**Suggested answer:**

There were two outcomes.

Technically, they independently delivered the implementation and test suite for a production-facing rate-limiting feature.

From a career-development perspective, they were able to explain the problem, architectural decisions, edge cases, and impact during their promotion evaluation.

They were promoted to SD2 in the following review cycle.

That combination of independent delivery and demonstrated technical ownership was the strongest evidence that the mentoring worked.

## Q5. What would you do differently?

**Suggested answer:**

I would establish explicit growth milestones at the beginning of the project.

For example, I would identify which competencies the engineer needed to demonstrate: design ownership, handling technical trade-offs, testing strategy, and production readiness.

That would make the development plan more intentional and give us a clearer way to evaluate progress throughout the project.

## Q6. How did you balance your own deliverables with mentoring?

**Suggested answer:**

I treated mentoring as part of the engineering responsibility rather than an additional activity.

I invested time upfront in explaining the architecture and the problem boundaries. This reduced the need for constant intervention later.

I also used design discussions and code reviews as opportunities to coach, rather than having separate sessions for every issue.

The engineer gradually became more independent, which allowed me to focus on broader architectural and production responsibilities.

## Q7. Did you ever disagree with your mentee's technical decisions?

**Suggested answer:**

Yes. The rate-limiter implementation itself had an example where their initial approach had a flaw.

Rather than immediately rejecting their implementation, I asked questions that helped them evaluate the assumptions behind their approach.

I believe disagreement is useful when it focuses on engineering reasoning rather than personal preference.

My responsibility was to ensure the production solution was correct while allowing them to develop ownership of the technical decisions.

## Q8. How did you ensure the solution was production-ready?

**Suggested answer:**

We focused on several aspects:

- Dedicated tests for rate-limit increase, decrease, and hold conditions.
- Edge cases involving idle and lightly loaded shards.
- Minimum and maximum rate boundaries.
- Independent rate limiting across tenant-shard combinations.
- Tenant-level configuration for controlled rollout.
- Metrics to observe the per-shard rate.

I reviewed these scenarios with the engineer to ensure we weren't only validating the happy path.

## Q9. What was the biggest technical challenge in this project?

**Suggested answer:**

One of the most important challenges was designing the feedback mechanism correctly.

A naive implementation could interpret low traffic as evidence of spare capacity and continuously increase the rate, even though the database had never been tested at that throughput.

We corrected this by measuring successful requests against the allocated allowance and reducing the rate only when actual failures crossed the threshold.

This was important because the controller needed to distinguish between insufficient workload and genuine database congestion.

## Q10. What was your biggest learning from mentoring this engineer?

**Suggested answer:**

I learned that ownership is one of the most effective ways to develop engineers.

Giving someone a well-defined but meaningful problem forces them to think beyond implementation details. They have to understand the business problem, make technical decisions, consider edge cases, and take responsibility for the outcome.

I also learned that asking the right question during a review can be much more valuable than providing the answer.

## Q11. How did you help the engineer get visibility for their work?

**Suggested answer:**

I made sure they were the primary owner of the implementation and testing, and that their contributions were visible in the engineering reviews.

I also coached them on presenting the work in terms of the original problem, architectural trade-offs, technical decisions, and production impact.

I wanted them to be able to independently explain and defend the solution rather than rely on me to communicate their contribution.

## Q12. What if the engineer had not been promoted?

**Suggested answer:**

I would still consider the mentoring successful if they had developed the necessary engineering capabilities and demonstrated greater independence.

Promotion decisions involve multiple factors and are not entirely within my control.

My responsibility as a mentor is to create opportunities, provide constructive feedback, and help engineers develop the competencies required for the next level.

I would have identified any remaining gaps and worked with them on a concrete development plan.

---

# 3. Technical Questions You Should Be Prepared For

Although this is primarily a Hire and Develop the Best story, Amazon interviewers may dig into the technical decisions to understand whether you genuinely owned the design.

| Question | What to cover |
|---|---|
| Why shard-level rather than tenant-level throttling? | Actual overload boundary and fault isolation |
| Why use tenant + shard as the limiter key? | Multiple tenants sharing shards and independent control |
| Why five-second windows? | Responsiveness versus noisy measurements |
| Why increase/decrease by 20%? | Proportional adaptation and stability |
| Why measure success against allowance? | Avoid confusing low traffic with demonstrated capacity |
| Why have minimum and maximum limits? | Prevent collapse and unbounded growth |
| What happens if a shard continuously returns 429s? | Backoff, floor, and retry behavior |
| What happens if the shard has no traffic? | Maintain the existing rate |
| How do you avoid unfairness between tenants? | Per-tenant-per-shard limits and fair scheduling |
| How do you roll back the feature? | Per-tenant configuration |
| How do you validate production behavior? | Metrics, alarms, rollout, and failure scenarios |

---

# 4. Key Points to Remember

| Amazon LP signal | Your evidence |
|---|---|
| Coach others | Explained architecture and trade-offs |
| Develop talent | Gave SD1 engineer SD2-level ownership |
| Invest in growth | Dedicated code reviews and technical guidance |
| Help others succeed | Asked questions instead of providing fixes |
| Raise the bar | Encouraged independent design reasoning |
| Demonstrate results | Engineer promoted to SD2 |

## Your strongest moment

Remember this exchange:

**You:** "What happens to the rate limit of a shard that receives no traffic during a particular window?"

**The engineering insight:** Measuring success against requests sent confuses successful processing of a small workload with proof of additional capacity.

**The outcome:** The mentee identified and corrected the issue by measuring success against the allocated allowance.

This is the strongest mentoring example in your story because it demonstrates that you helped the engineer develop independent technical judgment.

## Final interview advice

- Target 3–4 minutes for the initial story.
- Spend approximately 60% of your time on the mentoring and coaching aspects.
- Be precise about your role: you designed the architecture; your mentee owned implementation and tests.
- Use the idle-shard bug as your concrete coaching example.
- Clearly connect the work to the engineer's SD2 promotion.
- Don't claim numerical production improvements unless you have actual metrics to support them.

**One sentence to anchor your answer:**

"I didn't want to develop the engineer by giving them more tickets. I wanted to give them ownership of a real production problem, let them make meaningful technical decisions, and use my reviews to help them develop the judgment to solve problems independently."
