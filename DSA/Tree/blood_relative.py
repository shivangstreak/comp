from collections import defaultdict, deque

def are_blood_relatives(relations: list[list[str]], a: str, b: str) -> bool:
    parents = defaultdict(list)
    for parent, child in relations:
        parents[child].append(parent)

    def ancestors(person):
        found = {person}            # a person is their own ancestor
        queue = deque([person])
        while queue:
            cur = queue.popleft()
            for p in parents[cur]:
                if p not in found:
                    found.add(p)
                    queue.append(p)
        return found

    return len(ancestors(a) & ancestors(b)) > 0