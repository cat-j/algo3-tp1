import time

def fibbo(n):
    if n==0 or n ==1:
        return 1
    else:
        return fibbo(n-1)+fibbo(n-2)

if __name__ == "__main__":
    for n in range(1,21):
        for rep in range(10):
            start = time.time()
            res = fibbo(n)
            end = time.time()
            print(str(end-start))
