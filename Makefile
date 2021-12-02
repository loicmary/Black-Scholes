CC=g++
CFLAGS=-Wall 
LDFLAGS=
EXEC=main
SRC_DIR=src
BLD_DIR=build
BIN_DIR=bin
TEST_DIR=test

all: $(EXEC)

main: $(BLD_DIR)/main.o $(BLD_DIR)/bmatrix.o $(BLD_DIR)/tri_diag_matrix.o $(BLD_DIR)/col_vector.o $(BLD_DIR)/linear_system.o $(BLD_DIR)/payoff.o $(BLD_DIR)/put.o $(BLD_DIR)/call.o $(BLD_DIR)/implicit.o $(BLD_DIR)/cranck_nicholson.o $(BLD_DIR)/diff_finies.o  
	$(CC) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)




col_vector_test: $(BLD_DIR)/col_vector_test.o $(BLD_DIR)/bmatrix.o $(BLD_DIR)/col_vector.o
	$(CC) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)

tri_diag_matrix_test: $(BLD_DIR)/tri_diag_matrix_test.o $(BLD_DIR)/bmatrix.o $(BLD_DIR)/col_vector.o $(BLD_DIR)/tri_diag_matrix.o
	$(CC) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)

sys_lin_test: $(BLD_DIR)/sys_lin_test.o $(BLD_DIR)/linear_system.o $(BLD_DIR)/bmatrix.o $(BLD_DIR)/col_vector.o $(BLD_DIR)/tri_diag_matrix.o
	$(CC) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)

call_test: $(BLD_DIR)/call_test.o $(BLD_DIR)/payoff.o $(BLD_DIR)/call.o
	$(CC) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)

put_test: $(BLD_DIR)/put_test.o $(BLD_DIR)/payoff.o $(BLD_DIR)/put.o
	$(CC) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)

crk_test:  $(BLD_DIR)/cranck_nicholson_test.o $(BLD_DIR)/cranck_nicholson.o $(BLD_DIR)/payoff.o $(BLD_DIR)/put.o $(BLD_DIR)/call.o $(BLD_DIR)/bmatrix.o $(BLD_DIR)/col_vector.o $(BLD_DIR)/tri_diag_matrix.o $(BLD_DIR)/linear_system.o $(BLD_DIR)/diff_finies.o
	$(CC) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)

implicit_test:  $(BLD_DIR)/implicit_test.o $(BLD_DIR)/implicit.o $(BLD_DIR)/payoff.o $(BLD_DIR)/put.o $(BLD_DIR)/call.o $(BLD_DIR)/bmatrix.o $(BLD_DIR)/col_vector.o $(BLD_DIR)/tri_diag_matrix.o $(BLD_DIR)/linear_system.o $(BLD_DIR)/diff_finies.o
	$(CC) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)

$(BLD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(BLD_DIR)/*.o

mrproper: clean
	rm -rf $(EXEC)
