Mathematical problem: Beatty Sequence

Copied the solution from:

- https://surajshetiya.github.io/Google-foobar/
- https://vitaminac.github.io/Google-Foobar-Dodge-The-Lasers/
- https://math.stackexchange.com/questions/2052179/how-to-find-sum-i-1n-left-lfloor-i-sqrt2-right-rfloor-a001951-a-beatty-s

def Root_2_Floor(x):
    POWER_10 = long("100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000")
    SQRT_2 = long("41421356237309504880168872420969807856967187537694807317667973799073247846210703885038753432764157273501384623091229702492483605585073721264412149709993583141322266592750559275579995050115278206")
    
    ans = long((x*(x+1))/2)
    
    if x <= 10:
        for i in range(x):
            ans += long((SQRT_2*(i+1))/POWER_10)
        return ans
    
    last_term = long((SQRT_2 * x) / POWER_10)
    
    ans += (x * last_term ) - long((last_term * (last_term + 1))/2) - Root_2_Floor(last_term)
    
    return ans
    
def solution(s):
    return str(Root_2_Floor(long(s)))
