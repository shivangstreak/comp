import unittest

from collections import Counter


class Solution:
    def minWindow(self, s: str, t: str) -> str:
        mp_s = Counter()
        mp_t = Counter(t)
        l = 0
        r = 0
        res_length = float('inf')
        res_l = -1
        res_r = -1
        done = 0

        while r < len(s):
            mp_s[s[r]] += 1

            if mp_s[s[r]] == mp_t[s[r]]:
                done += 1

            while l <= r and done == len(mp_t):
                if r - l + 1 < res_length:
                    res_length = r - l + 1
                    res_l = l
                    res_r = r

                if mp_t[s[l]] > 0 and mp_s[s[l]] <= mp_t[s[l]]:
                    done -= 1

                mp_s[s[l]] -= 1
                l += 1

            r += 1

        if res_length == float('inf'):
            return ""

        return s[res_l:res_r + 1]




class SolutionTest(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_minWindow(self):
        # Example test cases
        s = "ADOBECODEBANC"
        t = "ABC"
        self.assertEqual(self.solution.minWindow(s, t), "BANC")

        s = "a"
        t = "a"
        self.assertEqual(self.solution.minWindow(s, t), "a")

        s = "a"
        t = "aa"
        self.assertEqual(self.solution.minWindow(s, t), "")

        # Additional test cases
        s = "ABCD"
        t = "ABC"
        self.assertEqual(self.solution.minWindow(s, t), "ABC")

        s = "ABC"
        t = "ABCD"
        self.assertEqual(self.solution.minWindow(s, t), "")

        s = "aabbbcccc"
        t = "abc"
        self.assertEqual(self.solution.minWindow(s, t), "abbc")

        s = "abbbbbbbcacbacbacbac"
        t = "cba"
        self.assertEqual(self.solution.minWindow(s, t), "bac")

        s = "abcdefghijklmnopqrstuvwxyz"
        t = "xyz"
        self.assertEqual(self.solution.minWindow(s, t), "xyz")

if __name__ == '__main__':
    unittest.main()
