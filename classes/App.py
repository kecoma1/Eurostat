"""
File where the app is defined
"""
from classes.Result import Result
from classes.Number import Number
from classes.Star import Star
import re


class App:
    """
    Class that defines an app.
    """

    def __init__(self):
        self.results = []
        self.numbers = []
        self.stars = []
        i = 1
        while i <= 50:
            self.numbers.append(Number(i))
            if i <= 12:
                self.stars.append(Star(i))
            i += 1

    def add_result(self, nums, stars):
        """
        Method to add the results

        :param nums: Nums of the result
        :param stars: Stars of the result
        :return: void
        """
        self.results.append(Result(nums, stars))

    def nums_together(self, nums):
        """
        Method to check if all the numbers in
        nums are in the same result
        :param nums: Numbers to check
        :return: Number of times that these numbers
        are together in the same result
        """
        n = 0
        for i in self.results:
            if i.nums_together(nums):
                n += 1
        return n

    def stars_together(self, stars):
        """
        Method to check if all the stars in
        stars are in the same result
        :param stars: Stars to check
        :return: Number of times that these stars
        are together in the same result
        """
        n = 0
        for i in self.results:
            if i.stars_together(stars):
                n += 1
        return n

    def read_results_from(self, file):
        """
        Method to read the results from a
        file and store them in the app

        :param file: File name where the results are
        :return: Void
        """
        try:
            nums = []
            stars = []
            f = open(file, "r")  # Opening the file
            while True:
                i = 0
                line = f.readline()

                if not line:
                    break

                nums_and_stars = re.findall('\d+', line)  # Storing the numbers and stars in a variable
                for digit in nums_and_stars:
                    if i < 5:  # Storing just numbers
                        self.numbers[int(digit)-1].appeared()
                        nums.append(int(digit))
                    else:
                        self.stars[int(digit)-1].appeared()
                        stars.append(int(digit))
                    i += 1

                self.add_result(nums, stars)
                nums.clear()
                stars.clear()
            f.close()

        except IOError:
            print("Could not read file:", file)

    def print_nums_info(self):
        """
        Method to print the numbers info

        :return: Void
        """
        print("\nNumbers:")
        n = 1
        for i in self.numbers:
            print('\033[94m', i.num, end=" ")
            if n < 10:
                print('\033[92m', i.appearances, end="\t")
            else:
                print('\033[92m', i.appearances)
                n = 0
            n += 1

    def print_stars_info(self):
        """
        Method to print the numbers info

        :return: Void
        """
        print('\033[5m', "\nStars:")
        n = 1
        for i in self.stars:
            print('\033[94m', i.star, end=" ")
            if n < 4:
                print('\033[92m', i.appearances, end="\t")
            else:
                print('\033[92m', i.appearances)
                n = 0
            n += 1

    def print_results(self):
        """
        Method to print the results of the app

        :return: Void
        """
        for i in self.results:
            print("Numbers: ", end=""),
            for n in range(5):
                print(i.nums[n], end="\t"),

            print("\tStars: ", end=""),
            for n in range(2):
                print(i.stars[n], end="\t"),

            print("")
