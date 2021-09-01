class Solution {
    public int maxProfit(int[] prices) {
        return maxProfit(prices, 0, 0, 0, true);
    }
    
    /**
     * It predicts the price in best-case (buy while cheaper, sell while expensive)
     * PRE: index < prices.length
     * O(n*log(n))
     */
    private int evaluate(int[] prices, int index, int acumulated, boolean isBuying) {
        // TODO pre-sort
        int []sorted = Arrays.copyOfRange(prices, index, prices.length);
        Arrays.sort(sorted); // O(n*log(n))
        
        int first = 0, last = sorted.length-1;
        // O(n)
        while (first < last || (first == last && !isBuying) /* if they're odd only use it if the last is selling */) {
            if (isBuying) {
                acumulated -= sorted[first];
                first++;
            }
            else {
                acumulated += sorted[last];
                last--;
            }
            isBuying = !isBuying;
        }
        
        return acumulated;
    }
    
    private int maxProfit(int[] prices, int index, int acumulated, int buyPrice, boolean isBuying) {
        if (prices.length-index == 0) return acumulated;
        //if (evaluate(prices, index, acumulated, isBuying) < 0) return acumulated; // no hope here...

        int resultPick = 0, resultIgnore = maxProfit(prices, index+1, acumulated, buyPrice, isBuying);

        if (isBuying) resultPick = maxProfit(prices, index+1, acumulated-prices[index], prices[index], false);
        else {
            // only sell if greater than the buy price
            if (prices[index] > buyPrice) resultPick = maxProfit(prices, index+1, acumulated+prices[index], prices[index], true);
        }

        return Math.max(Math.max(resultPick, resultIgnore), 0 /* do nothing (don't buy anything) */);
    }
}