#include<iostream>
#include<vector>

// Flood fill an image given a starting point (sr, sc) and new color newColor
// fill only 4 directionally connected pixels only
// color can be an int
// size is based on the imput vector

// Solution: to me it looks to be a simple DFS
// use Recursion to do it cheaply

// use -std=c++11 during compilation as the vector initializion is as per c++11.

class Solution {
private:
  void ff(std::vector<std::vector<int> >& image, int x, int y, int oldColor, int newColor) {
    image[x][y] = newColor;
    if (((x-1) >= 0) && (image[x-1][y] == oldColor)) ff(image, x-1, y, oldColor, newColor);
    if (((x+1) < image.size()) && (image[x+1][y] == oldColor)) ff(image, x+1, y, oldColor, newColor);
    if (((y-1) >= 0) && (image[x][y-1] == oldColor)) ff(image, x, y-1, oldColor, newColor);
    if (((y+1) < image[0].size()) && (image[x][y+1] == oldColor)) ff(image, x, y+1, oldColor, newColor);
    return;
    }
public:
  std::vector<std::vector<int> > floodFill(std::vector<std::vector<int> >& image, int sr, int sc, int newColor) {
    int oldColor = image[sr][sc];
    if (oldColor == newColor) return image;
    ff(image, sr, sc, oldColor, newColor);
    return image;
  }
};

int main(int argc, char *argv[])
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  // use -std=c++11 during compilation as the vector initializion is as per c++11.
  std::vector<std::vector<int> > image = { { 1, 1, 1 }, { 1, 1, 0 }, { 1, 0, 1 } };

  std::cout << "Before:\n";
  for (int r = 0; r < image.size(); ++r) {
    for (int c = 0; c < image[r].size(); ++c) {
      std::cout << image[r][c] << " ";
    }
    std::cout << std::endl;
  }

  Solution solution;
  std::vector<std::vector<int> > newImage = solution.floodFill(image, 1, 1, 2);

  std::cout << "After:\n";
  for (int r = 0; r < image.size(); ++r) {
    for (int c = 0; c < image[r].size(); ++c) {
      std::cout << image[r][c] << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
