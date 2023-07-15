#include <iostream>
#include <vector>

using namespace std;

void generateSudoku(vector<vector<int>> &grid, int row, int col) {
  // If we have reached the end of the grid, we are done.
  if (row == grid.size()) {
    return;
  }

  // If this cell is already filled, move on to the next one.
  if (grid[row][col] != 0) {
    generateSudoku(grid, row + 1, col);
    return;
  }

  // Try all possible values for this cell.
  for (int num = 1; num <= 9; num++) {
    // If this value is valid, fill the cell and recursively generate the rest of the grid.
    if (isValid(grid, row, col, num)) {
      grid[row][col] = num;
      generateSudoku(grid, row + 1, col);
    }
  }

  // If we have tried all possible values and none of them work, backtrack and try a different cell.
  grid[row][col] = 0;
}

bool isValid(vector<vector<int>> &grid, int row, int col, int num) {
  // Check if the number is already in this row.
  for (int i = 0; i < grid.size(); i++) {
    if (grid[i][col] == num) {
      return false;
    }
  }

  // Check if the number is already in this column.
  for (int i = 0; i < grid.size(); i++) {
    if (grid[row][i] == num) {
      return false;
    }
  }

  // Check if the number is already in this 3x3 block.
  int blockRow = row / 3;
  int blockCol = col / 3;
  for (int i = blockRow * 3; i < (blockRow + 1) * 3; i++) {
    for (int j = blockCol * 3; j < (blockCol + 1) * 3; j++) {
      if (grid[i][j] == num) {
        return false;
      }
    }
  }

  // The number is valid.
  return true;
}

int main() {
  vector<vector<int>> grid(9, vector<int>(9));
  generateSudoku(grid, 0, 0);

  // Print the generated grid.
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      cout << grid[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
}
