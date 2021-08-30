int maxProfitRecursive(int* prices, int pricesSize, bool isBuying);

int maxProfit(int* prices, int pricesSize) {
    return maxProfitRecursive(prices, pricesSize, true); // default
}

int maxProfitRecursive(int* prices, int pricesSize, bool isBuying) {
    if (pricesSize == 0) return 0;
    
    int resultPick = maxProfitRecursive(prices+1, pricesSize-1, !isBuying) + ((isBuying ? -1 : 1) * prices[0]),
        resultIgnore = maxProfitRecursive(prices+1, pricesSize-1, isBuying);
    
    int result = (resultPick > resultIgnore) ? resultPick : resultIgnore;
    return (result > 0) ? result : 0 /* do nothing */;
}