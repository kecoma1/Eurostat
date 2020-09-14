"""
File where the stars are defined
"""


class Star:

    def __init__(self, star):
        self.star = star
        self.appearances = 0

    def get_num(self):
        return self.star

    def appeared(self):
        self.appearances += 1

    def get_appearances(self):
        return self.appearances
