import numpy as np

def check_mat(binary_mat):
    for row in binary_mat:
        if row.sum() == 5:
            return True
    for col in binary_mat.T:
        if col.sum() == 5:
            return True
    return False

file = open('inputs/4.txt','r')
lines = file.readlines()
print(lines[0])

numbers = [int(x) for x in lines[0].split(',')]
matrices = []
binary_matrices = []
for i in range(2,len(lines),6):
    mat = np.zeros((5,5),dtype=int)
    for j in range(5):
        mat[j,:] = [int(x) for x in lines[i+j].split()]
    matrices.append(mat)
    binary_matrices.append(np.zeros((5,5),dtype=bool))

time_board_won = np.zeros(len(matrices),dtype=int)
score_board_won = np.zeros(len(matrices),dtype=int)
for number_index in range(len(numbers)):
    number = numbers[number_index]
    for i in range(len(matrices)):
        if time_board_won[i] != 0:
            continue
        binary_matrices[i] = np.logical_or(binary_matrices[i],matrices[i]==number)
        if check_mat(binary_matrices[i]):
            sum_unmarked = np.multiply(np.logical_not(binary_matrices[i]),matrices[i]).sum()
            time_board_won[i] = number_index
            score_board_won[i] = sum_unmarked * number
    
index = time_board_won.argmax()
print(score_board_won[index])