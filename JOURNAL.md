## Day 1

It's a mistake coding in C. Nevertheless, I managed to scrape through the whole thing. Admittedly, I overcomplicate, overengineer, and overefficientize everything. So it's mostly my fault.

In theory, this whole day's AoC could have been done using `vim` or `sed` + `bc`

### 1-1

The theory behind 1-1's code is simple: in that it's not.

1. Read the file line by line (max 64 char per line).
2. Turn all encountered digits to their int value ('0' -> 0, done by subtracting '0' or ascii val 30).
3. Bit shift to the left all encountered digits by 4*`k` where `k` is the amount of digits encountered starting from 0 (the logic being that the value 9 occupies only 4 bits).
4. Modulo `z` by `1 << 4` to get the first digit (and * 10 to make it the tenths).
5. Divide `z` by `1 << (4 * (k - 1))` to get the last digit.
6. Add the previous two together, add all the lines, and you get the total result.

### 1-2

1-2's code is blatant madness. Here's how the "logic" (if any) goes:

1. Read the file line by line (max 64 char per line).
2. Iterate through the line char by char.
3. If a digit is encountered:
    1. Turn it into a number (by subtracting '0').
    2. Set `xc` or `yc` to 1 (essentially locking it).
4. If any character in "otfsen" is found, then `numericmagify`:
    1. Check `len * 5` and prevent it from exceeding `sizeof(uint_fast32_t) * 8`, if exceeding, use `sizeof(uint_fast32_t) * 3 / 2` instead.
    2. Then, for every char in `str`, subtract by '\`' so that 'a' = 1, then bit shift left by 5*`i` (the logic being ``'z' - '`'`` is 5 bits long).
    3. Now check if the encountered chars really constitutes a number by checking the "magic"/"hash" against the number-word you want.
    4. If yes, set the number to `x` or `y` and set `xc` or `yc` to 1 (essentially locking it).

Note: the encounter is done from the front and behind of the `buf` even if it's 1 loop.
Note2: yes, `numericmagify` **is** a shabby, knockoff hash function.