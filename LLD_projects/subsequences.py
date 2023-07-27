def generate_subsequences(nums):
    def dfs(start, path):
        subsequences.append(path[:])

        for i in range(start, len(nums)):
            path.append(nums[i])
            dfs(i + 1, path)
            path.pop()

    subsequences = []
    dfs(0, [])
    return subsequences

a = [1,2,3,4,5]

print(generate_subsequences(a))


# All palindrome-partitioning for a string s
# class Solution:
#     def partition(self, s: str) -> List[List[str]]:
#         def dfs(start, s, ans, res):
#             if start == len(s):
#                 ans.append(res[:])
#                 return
#
#             for end in range(start, len(s)):
#                 if is_palindrome(s, start, end):
#                     res.append(s[start:end + 1])
#                     dfs(end + 1, s, ans, res)
#                     res.pop()
#
#         def is_palindrome(s, start, end):
#             while start < end:
#                 if s[start] != s[end]:
#                     return False
#                 start += 1
#                 end -= 1
#             return True
#
#         ans = []
#         res = []
#         dfs(0, s, ans, res)
#         return ans
