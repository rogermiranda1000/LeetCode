class Solution {
    public List<List<Integer>> threeSum(int[] nums) {
        LinkedHashSet<ArrayList<Integer>> values = new LinkedHashSet<>();
        
        for (int x = 0; x < nums.length-2; x++) {
            for (int y = x+1; y < nums.length-1; y++) {
                for (int z = y+1; z < nums.length; z++) {
                    if (nums[x]+nums[y] != -nums[z]) continue; // nums[x]+nums[y]+nums[z] == 0
                    
                    ArrayList<Integer> current = new ArrayList<>(3);
                    current.add(nums[x]);
                    current.add(nums[y]);
                    current.add(nums[z]);
                    Collections.sort(current);
                    values.add(current); // it will check for equal values; O(1)
                    break; // if there's more, they will be just repeated
                }
            }
        }
        
        return new ArrayList(values);
    }
}