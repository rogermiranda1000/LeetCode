class Solution {
    public List<List<Integer>> threeSum(int[] nums) {
        ArrayList<Integer> positive = new ArrayList<>(),
                            negative = new ArrayList<>();
        short zeros = 0;
        
        for (int num : nums) {
            if (num < 0) negative.add(num);
            else if (num > 0) positive.add(num);
            else zeros++;
        }
        
        Collections.sort(positive);
        Collections.sort(negative, Collections.reverseOrder()); // we want [-1, -2, ...]
        
        
        /** At this point we have all the positive values on the 'positive' list,
         *  and all the negative values on the 'negative' list, both sorted.
         *  We have also the number of zeros in 'zeros' variable.
         *  Also, time O(n*log(n)); space O(n)
         */
        
        
        // LinkedHashSet will check if the value already exists
        LinkedHashSet<ArrayList<Integer>> values = new LinkedHashSet<>();
        
        if (zeros >= 3) {
            // more than 3 zeros? then we have a full-zero set!
            ArrayList<Integer> tmp = new ArrayList<>(3);
            tmp.add(0); tmp.add(0); tmp.add(0);
            values.add(tmp);
        }
        if (zeros > 0) {
            // we have at least one zero; considering that we need to make groups of 3 that adds to 0
            // only leaves to the solutions that match the [-a,0,a] format
            
            ArrayList<Integer> small, big;
            if (positive.size() < negative.size()) {
                small = positive;
                big = negative;
            }
            else {
                small = negative;
                big = positive;
            }
            
            // we will do n times log(m) operations; it's better to have the big element to be logaritmic
            for (int e : small) {
                if (Collections.binarySearch(big, -e) >= 0) {
                    // found!
                    ArrayList<Integer> tmp = new ArrayList<>(3);
                    tmp.add(e); tmp.add(0); tmp.add(-e);
                    Collections.sort(tmp);
                    values.add(tmp);
                }
            }
        }
        
        
        // At this point, still time O(n*log(n)); space O(n)
        
        combine(values, positive, negative);
        combine(values, negative, positive);
        
        // time O(n^2 * log(n)); space O(n)
        
        return new ArrayList(values);
    }
    
    /**
     * It will take one element from 'oneList', then two elements from 'twoList' (the last one will be searched)
     * time O(n^2 * log(n)); space O(1)
     */
    void combine(LinkedHashSet<ArrayList<Integer>> values, ArrayList<Integer> oneList, ArrayList<Integer> twoList) {
        boolean twoListIsNegative = (twoList.size() > 0) && (twoList.get(0) < 0);
        for (int index1 = 0; index1 < oneList.size(); index1++) {
            int e1 = oneList.get(index1);
            
            for (int index2 = 0; index2 < twoList.size(); index2++) {
                // e3+e1+e2 = 0 -> e3 = -e1-e2
                int e3 = -e1-twoList.get(index2);
                
                // ((e3 == 0) || ((e3 > 0) && twoListIsNegative) || ((e3 < 0) && !twoListIsNegative))
                if ((e3 == 0) || ((e3 < 0) ^ twoListIsNegative)) {
                    // you can't find e3 on a list than only holds integers of its other signal
                    // otherwise, the solution e1 = -e2 was added before
                    // also, being the list ordered, this will only get worst (so better take another oneList value)
                    break;
                }
                
                int index = Collections.binarySearch(twoList, e3);
                if ((index < 0) || (index == index2 && (index2 == 0 || twoList.get(index2-1) != e3) && (index2+1 == twoList.size() || twoList.get(index2+1) != e3))) continue; // not found, or found but it's e2 (and that value isn't twice)
                
                ArrayList<Integer> tmp = new ArrayList<>(3);
                tmp.add(e1); tmp.add(twoList.get(index2)); tmp.add(e3);
                Collections.sort(tmp);
                values.add(tmp);
            }
        }
    }
}