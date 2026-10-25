# --- Data Section ---
.data
msg:      .asciiz "Hello, World!\n"
myNumber: .word   42

# --- Text (Code) Section ---
.text
main:
    addi $t0, $zero, 10