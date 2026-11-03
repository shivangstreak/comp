# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', nodes: 'List[TreeNode]') -> 'TreeNode':
        targets = set(nodes)
        def dfs(root):
            if not root:
                return None
            if root in targets:
                return root
            left = dfs(root.left)
            right = dfs(root.right)
            if left and right:
                return root
            if left:
                return left
            if right:
                return right
        return dfs(root)



# Similar Problem Below
# Problem Definition

# Hierarchy: The company structure is modeled as an N-ary tree where the CEO is at the root, and each employee has zero, one, or multiple direct reports. [1, 2]
# Goal: Given the root of the hierarchy and a list/group of employee nodes, find the lowest common manager (LCM)—the deepest node in the tree whose subtree contains every employee in the given group (where an employee is considered a descendant of themselves). [1, 2]

# from typing import List, Optional


# class Employee:
#     def __init__(self, name: str, reports: Optional[List["Employee"]] = None):
#         self.name = name
#         self.reports = reports or []


# def lowest_common_manager(root: Employee, group: List[Employee]) -> Optional[Employee]:
#     targets = set(group)          # dedupe; compare by node identity
#     k = len(targets)
#     if not root or k == 0:
#         return None

#     answer = None

#     def dfs(node: Employee) -> int:
#         """Return how many target employees are in node's subtree."""
#         nonlocal answer
#         count = 1 if node in targets else 0
#         for child in node.reports:
#             count += dfs(child)
#             if answer:            # already found deeper, stop early
#                 return count
#         if count == k and answer is None:
#             answer = node         # post-order => first hit is the deepest
#         return count

#     dfs(root)
#     return answer