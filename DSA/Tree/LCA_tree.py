# Answer to follow up without checking nodes existence
# node p and q might not be present
class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        self.count = 0

        def dfs(node):
            if not node:
                return None
            left = dfs(node.left)      # explore children FIRST (post-order)
            right = dfs(node.right)

            if node == p or node == q:
                self.count += 1
                return node            # node is p/q -> it's the candidate LCA
            if left and right:
                return node            # p and q are in different subtrees
            return left or right       # propagate whichever was found

        lca = dfs(root)
        return lca if self.count == 2 else None



# Node p and q are present in tree for sure

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        if root==None:
            return None
        if root==p or root==q:
            return root
        left = self.lowestCommonAncestor(root.left,p,q)
        right = self.lowestCommonAncestor(root.right,p,q)

        if(left!=None and right!=None):
            return root
        if(left==None and right==None):
            return None
        if(left!=None):
            return left
        if(right!=None):
            return right