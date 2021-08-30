// O(N) time; O(1) memory
int removeDuplicates(int* nums, int numsSize) {
    if (numsSize == 0) return 0;

    int placement = 1, preValue = nums[0];
    for (int x = 1; x < numsSize; x++) {
        if (preValue != nums[x]) {
            nums[placement++] = nums[x];
            preValue = nums[x];
        }
    }
    return placement;
}
