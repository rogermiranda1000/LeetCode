// O(n) time, O(1) space
int getMaxValue(int* height, int heightSize) {
    int max = 0;
    for (int x=0; x<heightSize; x++) {
        if (height[x] > max) max = height[x];
    }
    return max;
}

// It optimizes the input parameters by removing the borders that will lead to leaking water
// O(n) time, O(1) space
void removeBorders(int **height, int *heightSize) {
    while (*heightSize >= 2 && (*height)[0] <= (*height)[1]) {
        // remove first element
        (*height)++;
        (*heightSize)--;
    }
    while (*heightSize >= 2 && (*height)[*heightSize-1] <= (*height)[*heightSize-2]) (*heightSize)--;
    if (*heightSize == 1) *heightSize = 0; // just a pilar; no water
}

int trap(int* height, int heightSize) {
    removeBorders(&height, &heightSize);
    
    int maxVal = getMaxValue(height, heightSize);
    int water = 0, tmpWater;
    // O(n*m) time, O(1) space; n being heightSize, m being maxVal
    for (int row = maxVal; row >= 1; row++) {
        bool filling = false;
        for (int x = 0; x < heightSize; x++) {
            if (filling) {
                // filling -> increment counter and if next is higher stop filling
                tmpWater++;
                if (x+1 < heightSize && height[x+1] >= row) {
                    filling = false;
                    water += tmpWater;
                }
            }
            else {
                // not filling -> check if this spot is higher and the next spot is empty
                if (height[x] >= row && x+1 < heightSize && height[x+1] < row) {
                    filling = true;
                    tmpWater = 0;
                }
            }
        }
    }
    
    return water;
}