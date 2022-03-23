from primes import get_nth_prime


def main():
    # Get the 20,000th prime number
    N_TH = 20000
    nth_prime = get_nth_prime(N_TH)
    print(f"The {N_TH}-th prime is: {nth_prime}")


if __name__ == "__main__":
    main()
