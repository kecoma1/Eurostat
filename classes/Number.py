"""
File where the numbers are defined
"""


class Number:

    def __init__(self, num):
        self.num = num
        self.appearances = 0

    def get_num(self):
        return self.num

    def appeared(self):
        self.appearances += 1

    def get_appearances(self):
        return self.appearances
