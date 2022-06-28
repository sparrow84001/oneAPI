#Set Breakpoint in the Kernel
echo ================= (1) break 59 ===============\n
break 59
echo ================= (2) break 61 ===============\n
break 61

# Run the application on the GPU
echo ================= (3) run gpu ===============\n
run gpu

# Keep other threads stopped while current thread is stepped
echo ================= (4) set scheduler-locking step ===============\n
set scheduler-locking step 

echo ================= (5) next ===============\n
next 

echo ================= (6) info threads 2.* ===============\n
info threads 2.*

echo ================= (7) Print element ============\n
print element

# Switch thread
echo ================= (8) thread 2.1:5 =======================\n
thread 2.1:4

echo ================= (9) Print element ============\n
print element

echo ================= (10) thread apply 2.1:* print element =======================\n
thread apply 2.1:* print element

# Inspect vector of a local variable, 8 elements, integer word
echo ================= (11) x/8dw &result =======================\n
x /8dw &result

echo ================= (12) d 1 =======================\n
d 1
echo ================= (13) d 2 =======================\n
d 2
echo ================= (14) c ==========================\n
c 
