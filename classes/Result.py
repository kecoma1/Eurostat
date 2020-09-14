"""
File where the results are defined
"""


class Result:
    """
    Class that defines a result and all the operations
    """

    def __init__(self, nums, stars):
        self.nums = nums.copy()
        self.stars = stars.copy()

    def get_nums(self):
        return self.nums

    def get_stars(self):
        return self.stars

    def nums_together(self, nums):
        for i in nums:
            if not self.is_there_num(i):
                return False

        return True

    def stars_together(self, stars):
        for i in stars:
            if not self.is_there_star(i):
                return False

        return True

    def is_there_num(self, num):
        """
        Method to check if the number num is
        in the result.

        :param num: Number to check
        :return: Boolean value. True if it is, false if not
        """
        if num in self.nums:
            return True
        return False

    def is_there_star(self, star):
        """
        Method to check if a star is
        in the result.

        :param star: Star to check
        :return: Boolean value. True if it is, false if not
        """
        if star in self.stars:
            return True
        return False

    def __str__(self):
        return "Numbers: " + ' '.join(self.nums)+" Stars:" + ' '.join(self.stars)
