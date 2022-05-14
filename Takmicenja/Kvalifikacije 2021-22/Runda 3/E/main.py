from sympy import *
from sympy import Min,Max
import numpy as np
import matplotlib.pyplot as plt
import progressbar

def check_theorem1(expr):
    x = Symbol('x')
    min_value = expr.subs(x,-10000)
    max_value = expr.subs(x,10000)
    other_value_expr = None
    fanki = False
    for i in np.arange(-100,100):
        if expr.subs(x,i) != min_value and expr.subs(x,i) != max_value:
            if other_value_expr == None:
                c = expr.subs(x,i) - i
                other_value_expr = x + c
                fanki = True
            elif other_value_expr.subs(x,i) != expr.subs(x,i):
                return False
    return True, fanki

def transform_expr(constants, func_type):
    # 0 = min, 1 = max, 2 = add
    from_add = 0
    for i in range(len(func_type)):
        if func_type[i] == 2:
            from_add += constants[i]
            constants[i] = 0
        else:
            constants[i] -= from_add

    func_type = np.append(func_type,0)
    constants = np.append(constants, from_add)
    return constants, func_type

def check_theorem2(expr, constants, func_type):
    start_expr, start_str = construct_function(constants, func_type)
    constants, func_type = transform_expr(constants, func_type)
    
    alt_expr, alt_str = construct_function(constants, func_type)
    diff = expr - alt_expr
    if diff != 0:
        x = Symbol('x')
        x_check = np.random.randint(-500,500,250)
        for i in range(len(x_check)):
            if simplify(diff.subs(x,x_check[i])) != 0:
                return False
    return True

def check_theorem3(expr, constants, func_type):
    constants, func_type = transform_expr(constants, func_type)

    x = Symbol('x')
    min_value = simplify(expr.subs(x,-100000))
    max_value = simplify(expr.subs(x,100000))
    other_value_expr = None
    for i in np.arange(-100,100):
        if expr.subs(x,i) != min_value and expr.subs(x,i) != max_value:
            c = expr.subs(x,i) - i
            other_value_expr = x + c
        
        if other_value_expr == None:
            return True
        else:
            middle_expr = simplify(other_value_expr - (x+constants[-1]))
            if middle_expr == 0:
                return True  
            else:
                return False
    else:
        return True
                


def construct_function(constants, func_type):
    # 0 = min, 1 = max, 2 = add
    x = Symbol('x')
    expr = x
    func_str = "x"
    for i in range(len(constants)):
        if func_type[i] == 2:
            expr = expr + constants[i]
            func_str = func_str + "+" + str(constants[i])
        elif func_type[i] == 1:
            expr = Max(expr,constants[i])
            func_str = "Max(" + func_str + "," + str(constants[i]) + ")"
        else:
            expr = Min(expr,constants[i])
            func_str = "Min(" + func_str + "," + str(constants[i]) + ")"
        print(expr)
    return expr, func_str

def generate_function(max_func_count = 20):
    func_count = np.random.randint(1,max_func_count)
    x = Symbol('x')
    expr = x
    constants = np.random.randint(-20,20,func_count)
    func_type = np.random.randint(0,3,func_count)
    expr, _ = construct_function(constants, func_type)
    return expr,constants, func_type

# tests = 10000
# bar = progressbar.ProgressBar(max_value=tests)
# fankile_cnt = 0

# for _ in range(tests):
#     expr, constants, func_type = generate_function()    
#     if not check_theorem3(expr, constants, func_type):
#         print('SMRT')
#         ex,s = construct_function(constants, func_type)
#         print(s)
#         check_theorem3(ex, constants, func_type)
#     else:
#         bar.update(bar.value+1)
# print(fankile_cnt)

func_types = np.array([1, 1, 2, 2, 1, 2, 3, 2, 1, 3],dtype=int)
func_types -= 1
constants = np.array([0, 10, -7, -15, -13, -7, -4, 4, 12, -15],dtype=int)
expr, expr_str = construct_function(constants, func_types)
print(expr_str)