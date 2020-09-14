"""
Main file of the application
"""
from classes.App import App
import re

# Declaring the app
app = App()

# Reading the results
app.read_results_from("results.txt")

# Printing info
app.print_results()
app.print_nums_info()
app.print_stars_info()

# Asking for combinations of numbers
while True:
    try:
        print("\nIntroduce the numbers to check ('quit' to skip)")
        print("All separated by a space. Example: 1 2 12 34 45")
        input1 = input("Introduce the numbers: ")

        if input1 == "quit":
            break
        numbers = re.findall('\d+', input1)

        if numbers.__len__() == 0:
            print("Just digits")
            continue

        nums_list = []

        for digit in numbers:
            nums_list.append(int(digit))

        print("Those numbers appeared together", app.nums_together(nums_list), "times")

        print("\nIntroduce the stars to check ('quit' to skip)")
        print("All separated by a space. Example: 1 2")
        input1 = input("Introduce the numbers: ")

        if input1 == "quit":
            break
        numbers = re.findall('\d+', input1)

        if numbers.__len__() == 0:
            print("Just digits")
            continue

        nums_list = []

        for digit in numbers:
            nums_list.append(int(digit))

        print("Those stars appeared together", app.stars_together(nums_list), "times")

    except ValueError:
        print("Just digits")
