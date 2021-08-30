int maxProfitRecursive(int* prices, int pricesSize, int buyPrice, bool isBuying);

int maxProfit(int* prices, int pricesSize) {
    return maxProfitRecursive(prices, pricesSize, 0, true); // default
}

int maxProfitRecursive(int* prices, int pricesSize, int buyPrice, bool isBuying) {
    if (pricesSize == 0) return 0;
    
    int resultPick = 0, resultIgnore = maxProfitRecursive(prices+1, pricesSize-1, buyPrice, isBuying);
    
    if (!isBuying) {
        // only sell if greater than the buy price
        if (prices[0] > buyPrice) resultPick = maxProfitRecursive(prices+1, pricesSize-1, prices[0], true) + prices[0];
    }
    else resultPick = maxProfitRecursive(prices+1, pricesSize-1, prices[0], false) - prices[0];
    
    int result = (resultPick > resultIgnore) ? resultPick : resultIgnore;
    return (result > 0) ? result : 0 /* do nothing */;
}