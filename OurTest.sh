echo "[Tests start]"
echo "[Test ComputersOnly]"
cat tests/computersOnly.txt | ./straights > tests/CP1
cat tests/computersOnly.txt | ~/Downloads/./straights > tests/CP2
diff tests/CP1 tests/CP2
echo "[Test ComputersOnly finished]"

echo "[Test ComputersOnlySeed44]"
cat tests/computersOnly.txt | ./straights 44 > tests/CP1
cat tests/computersOnly.txt | ~/Downloads/./straights 44 > tests/CP2
diff tests/CP1 tests/CP2
echo "[Test ComputersOnlySeed44 finished]"

echo "[Test discardNotInHand]"
cat tests/discardNotInHandtest.txt | ./straights > tests/CP1
cat tests/discardNotInHandtest.txt | ~/Downloads/./straights > tests/CP2
diff tests/CP1 tests/CP2
echo "[Test discardNotInHand finished]"

echo "[Test ragequitQuit]"
cat tests/ragequitQuit.txt | ./straights > tests/CP1
cat tests/ragequitQuit.txt | ~/Downloads/./straights > tests/CP2
diff tests/CP1 tests/CP2
echo "[Test ragequitQuit finished]"

echo "[Test everyoneRageQuits]"
cat tests/everyoneRageQuits.txt | ./straights > tests/CP1
cat tests/everyoneRageQuits.txt | ~/Downloads/./straights > tests/CP2
diff tests/CP1 tests/CP2
echo "[Test everyoneRageQuits finished]"

echo "[Test commandsAfterEnd]"
cat tests/commandsAfterEnd.txt | ./straights > tests/CP1
cat tests/commandsAfterEnd.txt | ~/Downloads/./straights > tests/CP2
diff tests/CP1 tests/CP2
echo "[Test commandsAfterEnd finished]"

echo "[Test blindAdding]"
cat tests/blindAdding.txt | ./straights > tests/CP1
cat tests/blindAdding.txt | ~/Downloads/./straights > tests/CP2
diff tests/CP1 tests/CP2
echo "[Test blindAdding finished]"

echo "[Test deck]"
cat tests/deck.txt | ./straights > tests/CP1
cat tests/deck.txt | ~/Downloads/./straights > tests/CP2
diff tests/CP1 tests/CP2
echo "[Test deck finished]"

echo "[Test discard7H]"
cat tests/discard7H.txt | ./straights > tests/CP1
cat tests/discard7H.txt | ~/Downloads/./straights > tests/CP2
diff tests/CP1 tests/CP2
echo "[Test discard7H finished]"

echo "[Test playNonExistant]"
cat tests/playNonExistant.txt | ./straights > tests/CP1
cat tests/playNonExistant.txt | ~/Downloads/./straights > tests/CP2
diff tests/CP1 tests/CP2
echo "[Test playNonExistant finished]"

echo "[Test spaces]"
cat tests/spaces.txt | ./straights  > tests/CP1
cat tests/spaces.txt | ~/Downloads/./straights  > tests/CP2
diff tests/CP1 tests/CP2
echo "[Test spaces finished]"

echo "[Test spaces123]"
cat tests/spaces.txt | ./straights 123 > tests/CP1
cat tests/spaces.txt | ~/Downloads/./straights 123 > tests/CP2
diff tests/CP1 tests/CP2
echo "[Test spaces123 finished]"

echo "[Test spaces32769]"
cat tests/spaces.txt | ./straights  32769> tests/CP1
cat tests/spaces.txt | ~/Downloads/./straights  32769> tests/CP2
diff tests/CP1 tests/CP2
echo "[Test spaces32769 finished]"

echo "[Tests done]"
