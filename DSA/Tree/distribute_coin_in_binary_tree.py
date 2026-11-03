# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def distributeCoins(self, root: Optional[TreeNode]) -> int:
        moves = 0

        def dfs(node):
            nonlocal moves
            if not node:
                return 0
            left_coins = dfs(node.left)
            right_coins = dfs(node.right)
            moves += abs(left_coins) + abs(right_coins)

            return (node.val-1) + left_coins + right_coins
        dfs(root)

        return moves