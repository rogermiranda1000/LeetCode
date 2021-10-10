void rotate(int* nums, int numsSize, int k) {
    int aux;
    while (k > 0) {
        aux = nums[numsSize-1];
        memmove(&nums[1], nums, sizeof(int)*(numsSize-1));
        nums[0] = aux;
        
        k--;
    }
}
