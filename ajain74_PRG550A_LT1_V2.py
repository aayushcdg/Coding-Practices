# author:  Aayush Jain
# date:    October 19th, 2023

import math
import random
import string
import collections
import datetime
import re
import time
import copy
from functools import reduce


# Function to check if chemical equations are balanced
def isBalancedEquation(fileName):
    results = []

    try:
        # Open the file for reading
        with open(fileName, 'r') as file:
            # Loop through each line in the file
            for line in file:
                equation = line.strip()
                arrow_index = equation.find("->")

                if arrow_index == -1:
                    # If no arrow symbol found, the equation is not balanced
                    results.append({equation: False})
                else:
                    left_side = equation[:arrow_index].strip()
                    right_side = equation[arrow_index + 2:].strip()

                    # Initialize dictionaries to count elements on both sides
                    left_elements = {}
                    right_elements = {}

                    # Parse and count elements on the left side
                    elements = re.findall(r'([A-Z][a-z])(\d)', left_side)
                    for element, count in elements:
                        count = int(count) if count else 1
                        left_elements[element] = left_elements.get(element, 0) + count

                    # Parse and count elements on the right side
                    elements = re.findall(r'([A-Z][a-z])(\d)', right_side)
                    for element, count in elements:
                        count = int(count) if count else 1
                        right_elements[element] = right_elements.get(element, 0) + count

                    # Check if the equation is balanced by comparing element counts
                    is_balanced = left_elements == right_elements
                    results.append({equation: is_balanced})

    except FileNotFoundError:
        print("File not found.")

    return results


# end def
