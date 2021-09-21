class Solution {
    class SolutionInstance {
        public int index;
        public int acumulated;
        public int buyPrice;
        public boolean isBuying;
        
        public SolutionInstance(int index, int acumulated, int buyPrice, boolean isBuying) {
            this.index = index;
            this.acumulated = acumulated;
            this.buyPrice = buyPrice;
            this.isBuying = isBuying;
        }
    }
    
    class Evaluation {
        private int index;
        private boolean isBuying;
        
        public Evaluation(int index, boolean isBuying) {
            this.index = index;
            this.isBuying = isBuying;
        }
        
        @Override
        public boolean equals(Object o) {
            if (o == null || !(o instanceof Evaluation)) return false;
            Evaluation that = (Evaluation)o;
            //return this.index == that.index && this.isBuying == that.isBuying;
            return this.hashCode() == that.hashCode();
        }

        @Override
        public int hashCode() {
            return index*2 + (isBuying ? 1 : 0);
        }
    }
    
    private HashMap<Evaluation,Integer> cache;
    
    public int maxProfit(int[] prices) {
        PriorityQueue<SolutionInstance> numbers = new PriorityQueue<>((a,b)->Integer.compare(a.acumulated, b.acumulated));
        numbers.add(new SolutionInstance(0,0,0,true)); // default one
        cache = new HashMap<>();
        
        int max = 0;
        while (!numbers.isEmpty()) {
            SolutionInstance current = numbers.remove();
            
            if (prices.length-current.index == 0) {
                max = Math.max(max, current.acumulated);
                continue;
            }
            if (evaluate(prices, current.index, current.acumulated, current.isBuying) < max) continue; // no hope here...

            numbers.add(new SolutionInstance(current.index+1, current.acumulated, current.buyPrice, current.isBuying));

            if (current.isBuying) numbers.add(new SolutionInstance(current.index+1, current.acumulated-prices[current.index], prices[current.index], false));
            else {
                // only sell if greater than the buy price
                if (prices[current.index] > current.buyPrice) numbers.add(new SolutionInstance(current.index+1, current.acumulated+prices[current.index], prices[current.index], true));
            }
        }
        
        return max;
    }
    
    /**
     * It predicts the price in best-case (buy while cheaper, sell while expensive)
     * PRE: index < prices.length
     * O(n*log(n)) if not cache; O(1) otherwise
     */
    private int evaluate(int[] prices, int index, int acumulated, boolean isBuying) {
        Evaluation search = new Evaluation(index, isBuying);
        
        Integer result = cache.get(search); // result from the current position to the last
        if (result == null) {
            int []sorted = Arrays.copyOfRange(prices, index, prices.length);
            Arrays.sort(sorted); // O(n*log(n))
            
            result = 0;
            int first = 0, last = sorted.length-1;
            // O(n)
            while (first < last || (first == last && !isBuying) /* if they're odd only use it if the last is selling */) {
                if (isBuying) {
                    result -= sorted[first];
                    first++;
                }
                else {
                    result += sorted[last];
                    last--;
                }
                isBuying = !isBuying;
            }
            
            cache.put(search, result);
        }
        
        return result+acumulated;
    }
}