void removeInitialBorder(int **height, int *heightSize) {
    while (*heightSize >= 2 && (*height)[0] <= (*height)[1]) {
        (*height)++;
        (*heightSize)--;
    }
}

// It optimizes the input parameters by removing the borders that will lead to leaking water
// O(n) time, O(1) space
inline void removeBorders(int **height, int *heightSize) {
    removeInitialBorder(height, heightSize);
    while (*heightSize >= 2 && (*height)[*heightSize-1] <= (*height)[*heightSize-2]) (*heightSize)--;
}

// It generates a ray on (*height)[0] and it returns the hit height (return value >= (*height)[0])
// If it doesn't hit with anything it returns the hightest block of all iterated blocks
// PRE: *heightSize > 1
inline int getHit(int **height, int *heightSize) {
    int next = 0;
    for (int x = 1; x < *heightSize; x++) {
        int current = (*height)[x];
        if (current>=(*height)[0]) return current;
        if (current>next) next = current;
    }
    return next; // no hit
}

// PRE: *heightSize > 1
inline int getHeightRay(int **height, int *heightSize) {
    int hit = getHit(height, heightSize);
    if (hit >= (*height)[0]) return (*height)[0];
    else return hit;
}

int trap(int* height, int heightSize) {
    removeBorders(&height, &heightSize);
    
    int water = 0;
    while (heightSize > 2) {
        int ray = getHeightRay(&height, &heightSize);
        int x = 1;
        while (x < heightSize && height[x] < ray) {
            water += ray-height[x];
            x++;
        }

        heightSize -= x;
        height += x;
        removeInitialBorder(&height, &heightSize);
    }
    return water;
}