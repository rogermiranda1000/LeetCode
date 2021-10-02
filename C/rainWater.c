// It optimizes the input parameters by removing the borders that will lead to leaking water
// O(n) time, O(1) space
void removeBorders(int **height, int *heightSize) {
    while (*heightSize >= 2 && (*height)[0] <= (*height)[1]) {
        // remove first element
        (*height)++;
        (*heightSize)--;
    }
    while (*heightSize >= 2 && (*height)[*heightSize-1] <= (*height)[*heightSize-2]) (*heightSize)--;
}

int trap(int* height, int heightSize) {
    removeBorders(&height, &heightSize);
    
    int water = 0;
    while (heightSize > 2) {
        int ray = height[0], tmpWater = 0;
        int x = 1;
        while (x < heightSize && height[x] < ray) {
            tmpWater += ray-height[x];
            x++;
        }

        if (x < heightSize) {
            // something hit the ray -> add water and remove that section
            water += tmpWater;
            heightSize -= x;
            height += x;
            removeBorders(&height, &heightSize);
        }
        else height[0]--; // try again with a lower height
    }
    return water;
}