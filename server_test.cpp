#include <gtest/gtest.h>

extern "C" {
  #include "server.c"
}



TEST(SERVER_INIT_CORRECT_SUCCESS, Assert_1) {
  char dns[16] = "server";
  char ip[16] = "111.111.111.11";
  char mask[16] = "255.255.255.255";
  int processor = 4;
  int core = 8;
  server network;
  int s = 1;
  int* success = &s;
  server real_server = server_init(dns, ip, mask, processor, core, success);
  EXPECT_EQ(s, 1);
}

TEST(SERVER_INIT_CORRECT_EQUAL, Assert_1) {
  char dns[] = "server";
  char ip[] = "111.111.111.11";
  char mask[] = "255.255.255.255";
  int processor = 4;
  int core = 8;
  server expected_network, real_network;
  strncpy(real_network.dns, dns, 16 * sizeof(char));
  strncpy(real_network.ip, ip, 16 * sizeof(char));
  strncpy(real_network.mask, mask, 16 * sizeof(char));
  real_network.processor = processor;
  real_network.core = core;
  int s = 1;
  int* success = &s;
  bool equals = true;
  expected_network = server_init(dns, ip, mask, processor, core, success);
  if (strcmp(real_network.dns, expected_network.dns) ||\
      strcmp(real_network.ip, expected_network.ip) || \
      strcmp(real_network.mask, expected_network.mask) || \
      real_network.processor != expected_network.processor || \
      real_network.core!=expected_network.core ) {
        equals = false;
      }
  EXPECT_EQ(equals, true);
  
}

TEST(SERVER_INIT_INCORRECT_DNS, Assert_1) {
  char dns[] = "servernegfvngjfknlgflbkjfnbjlbjlnglfdjvnjbjvnbjnjfnj";
  char ip[] = "111.111.111.11";
  char mask[] = "255.255.255.255";
  int processor = 4;
  int core = 8;
  server network;
  int s = 1;
  int* success = &s;
  server real_server = server_init(dns, ip, mask, processor, core, success);
  EXPECT_EQ(s, 0);
}

TEST(SERVER_INIT_INCORRECT_IP_LEN, Assert_1) {
  char dns[] = "server";
  char ip[] = "111.111.111.1111111";
  char mask[] = "255.255.255.255";
  int processor = 4;
  int core = 8;
  server network;
  int s = 1;
  int* success = &s;
  server real_server = server_init(dns, ip, mask, processor, core, success);
  EXPECT_EQ(s, 0);
}

TEST(SERVER_INIT_INCORRECT_IP_FORMAT, Assert_1) {
  char dns[] = "server";
  char ip[] = "111.111";
  char mask[] = "255.255.255.255";
  int processor = 4;
  int core = 8;
  server network;
  int s = 1;
  int* success = &s;
  server real_server = server_init(dns, ip, mask, processor, core, success);
  EXPECT_EQ(s, 0);
}


TEST(SERVER_INIT_INCORRECT_IP_BIG_NUMS, Assert_1) {
  char dns[] = "server";
  char ip[] = "911.111.111.111";
  char mask[] = "255.255.255.255";
  int processor = 4;
  int core = 8;
  server network;
  int s = 1;
  int* success = &s;
  server real_server = server_init(dns, ip, mask, processor, core, success);
  EXPECT_EQ(s, 0);
}

TEST(SERVER_INIT_INCORRECT_IP_NEGATIVE_NUMS, Assert_1) {
  char dns[] = "server";
  char ip[] = "111.111.-20.111";
  char mask[] = "255.255.255.255";
  int processor = 4;
  int core = 8;
  server network;
  int s = 1;
  int* success = &s;
  server real_server = server_init(dns, ip, mask, processor, core, success);
  EXPECT_EQ(s, 0);
}

TEST(SERVER_INIT_INCORRECT_IP_SYMBOLS, Assert_1) {
  char dns[] = "server";
  char ip[] = "111.111.abc.111";
  char mask[] = "255.255.255.255";
  int processor = 4;
  int core = 8;
  server network;
  int s = 1;
  int* success = &s;
  server real_server = server_init(dns, ip, mask, processor, core, success);
  EXPECT_EQ(s, 0);
}

TEST(SERVER_INIT_INCORRECT_MASK_LEN, Assert_1) {
  char dns[] = "server";
  char ip[] = "111.111.111.111";
  char mask[] = "255.255.255.255111";
  int processor = 4;
  int core = 8;
  server network;
  int s = 1;
  int* success = &s;
  server real_server = server_init(dns, ip, mask, processor, core, success);
  EXPECT_EQ(s, 0);
}

TEST(SERVER_INIT_INCORRECT_MASK_FORMAT, Assert_1) {
  char dns[] = "server";
  char ip[] = "111.111.111.111";
  char mask[] = "255.255.255";
  int processor = 4;
  int core = 8;
  server network;
  int s = 1;
  int* success = &s;
  server real_server = server_init(dns, ip, mask, processor, core, success);
  EXPECT_EQ(s, 0);
}


TEST(SERVER_INIT_INCORRECT_MASK_BIG_NUMS, Assert_1) {
  char dns[] = "server";
  char ip[] = "111.111.111.111";
  char mask[] = "355.255.255.255";
  int processor = 4;
  int core = 8;
  server network;
  int s = 1;
  int* success = &s;
  server real_server = server_init(dns, ip, mask, processor, core, success);
  EXPECT_EQ(s, 0);
}

TEST(SERVER_INIT_INCORRECT_MASK_NEGATIVE_NUMS, Assert_1) {
  char dns[] = "server";
  char ip[] = "111.111.111.111";
  char mask[] = "255.-20.255.255";
  int processor = 4;
  int core = 8;
  server network;
  int s = 1;
  int* success = &s;
  server real_server = server_init(dns, ip, mask, processor, core, success);
  EXPECT_EQ(s, 0);
}

TEST(SERVER_INIT_INCORRECT_MASK_SYMBOLS, Assert_1) {
  char dns[] = "server";
  char ip[] = "111.111.111.111";
  char mask[] = "255.cd5.255.255";
  int processor = 4;
  int core = 8;
  server network;
  int s = 1;
  int* success = &s;
  server real_server = server_init(dns, ip, mask, processor, core, success);
  EXPECT_EQ(s, 0);
}


TEST(SERVER_INIT_INCORRECT_PROCESSOR, Assert_1) {
  char dns[16] = "server";
  char ip[16] = "111.111.111.11";
  char mask[16] = "255.255.255.255";
  int processor = -1;
  int core = 8;
  server network;
  int s = 1;
  int* success = &s;
  server real_server = server_init(dns, ip, mask, processor, core, success);
  EXPECT_EQ(real_server.processor, 1);
}

TEST(SERVER_INIT_INCORRECT_CORE, Assert_1) {
  char dns[16] = "server";
  char ip[16] = "111.111.111.11";
  char mask[16] = "255.255.255.255";
  int processor = 4;
  int core = 0;
  server network;
  int s = 1;
  int* success = &s;
  server real_server = server_init(dns, ip, mask, processor, core, success);
  EXPECT_EQ(real_server.core, 1);
}

TEST(GET_NETWORK_ADRESS, ASSERT_TRUE) {
  int net_adr[ADR_NUM_SIZE] = {};
  char dns[16] = "server";
  char ip[16] = "111.111.111.111";
  char mask[16] = "255.255.255.255";
  int processor = 4;
  int core = 4;
  int s = 1;
  int* success = &s;
  server real_server = server_init(dns, ip, mask, processor, core, success);
  get_network_adress(real_server, net_adr);
  bool flag = true;
  for (int i = 0; i < ADR_NUM_SIZE; ++i) {
    if (net_adr[i]!=111) {
      flag = false;
      break;
    }
  }
  EXPECT_TRUE(flag);
}

TEST(GET_NETWORK_ADRESS_NULL, ASSERT_FALSE) {
  int *net_adr;
  net_adr = NULL;
  char dns[16] = "server";
  char ip[16] = "111.111.111.111";
  char mask[16] = "255.255.255.255";
  int processor = 4;
  int core = 4;
  int s = 1;
  int* success = &s;
  server real_server = server_init(dns, ip, mask, processor, core, success);
  get_network_adress(real_server, net_adr);
  EXPECT_FALSE(net_adr);
}



TEST(GET_ADDRESS_NUM_CORRECT, Assert_1) {
  int expected_arr[ADR_NUM_SIZE] = { 255, 255, 255, 255 };
  char str[] = "255.255.255.255";
  int real_arr[ADR_NUM_SIZE] = { 0 };
  get_adress_nums(str, real_arr);
  EXPECT_EQ(real_arr[0], expected_arr[0]);
}


TEST(GET_ADDRESS_NUM_NULL, ASSERT_FALSE) {
  int expected_arr[ADR_NUM_SIZE] = { 255, 255, 255, 255 };
  char str[] = "255.255.255.255";
  int *real_arr = NULL;
  get_adress_nums(str, real_arr);
  EXPECT_FALSE(real_arr);
}


TEST(GET_ADDRESS_STR_CORRECT, Assert_1) {
  char expected_str[] = "111.111.111.111";
  char *str = (char*)malloc(ADR_STR_SIZE * sizeof(char));
  int arr[4] = { 111, 111, 111, 111 };
  get_address_str(arr, str);
  EXPECT_EQ(strcmp(str, expected_str), 0);
  free(str);
}

TEST(GET_ADDRESS_STR_NULL, ASSERT_FALSE) {
  char expected_str[] = "111.111.111.111";
  char *str = NULL;
  int arr[] = { 111, 111, 111, 111 };
  get_address_str(arr, str);
  EXPECT_FALSE(str);
  free(str);
}

TEST(SET_INIT_CORRECT, ASSERT_TRUE) {
  set net = set_init(1);
  EXPECT_TRUE(net.max_size == 1 && net.cur_size == 0);
  set_destroy(&net);
}

TEST(SET_INIT_INCORRECT, ASSERT_TRUE) {
  set net = set_init(-5);
  EXPECT_TRUE(net.max_size == 0 && net.cur_size == 0);
  set_destroy(&net);
}


TEST(IN_SET_TRUE, ASSERT_TRUE) {
  int adr[] = { 111, 111, 111, 111 };
  char str[] = "111.111.111.111";
  set net = set_init(1);
  add_to_set(adr, &net);
  EXPECT_TRUE(in_set(str, net.host, net.cur_size));
  set_destroy(&net);
}

TEST(IN_SET_FALSE, ASSERT_FALSE) {
  int adr[] = { 111, 111, 111, 111 };
  char str[] = "111.111.111.0";
  set net = set_init(1);
  add_to_set(adr, &net);
  EXPECT_FALSE(in_set(str, net.host, net.cur_size));
  set_destroy(&net);
}

TEST(ADD_TO_SET_ORIGIN, ASSERT_TRUE) {
  int adr[] = { 111, 111, 111, 111 };
  char str[] = "111.111.111.111";
  set net = set_init(1);
  add_to_set(adr, &net);
  EXPECT_TRUE((net.cur_size == 1) && !(strcmp(net.host[0], str)));
  set_destroy(&net);
}

TEST(ADD_TO_SET_TWIN, ASSERT_TRUE) {
  int adr[] = { 111, 111, 111, 111 };
  char str[] = "111.111.111.111";
  set net = set_init(1);
  add_to_set(adr, &net);
  add_to_set(adr, &net);
  EXPECT_TRUE((net.cur_size == 1) && !(strcmp(net.host[0], str)));
  set_destroy(&net);
}

TEST(ADD_TO_SET_NULL, ASSERT_FALSE) {
  int *adr = NULL;
  set net = set_init(1);
  add_to_set(adr, &net);
  EXPECT_FALSE(net.cur_size);
  set_destroy(&net);
}


TEST(ADD_TO_SET_OVERFLOW, ASSERT_TRUE) {
  int adr[] = { 111, 111, 111, 111 };
  int adr2[] = { 111, 111, 111, 222 };
  char str[] = "111.111.111.222";
  set net = set_init(1);
  add_to_set(adr, &net);
  add_to_set(adr2, &net);
  EXPECT_TRUE((net.cur_size == 1) && !(in_set(str, net.host, net.cur_size)));
  set_destroy(&net);
}

TEST(UNIQUE_NETS_TO_SET, ASSERT_TRUE) {
  server *network = create_servers_arr(2);
  char dns[16] = "server";
  char ip1[16] = "111.111.111.111";
  char ip2[16] = "111.111.111.111";
  char mask[16] = "255.255.255.255";
  int processor = 4;
  int core = 4;
  int success = 1;
  network[0] = server_init(dns, ip1, mask, processor, core, &success);
  network[1] = server_init(dns, ip2, mask, processor, core, &success);
  set group = unique_nets_to_set(network, 2);
  EXPECT_TRUE((in_set(ip1, group.host, group.cur_size)) && (in_set(ip2, group.host, group.cur_size)));
  set_destroy(&group);
  destoy_servers_arr(network);
}


TEST(UNIQUE_NETS_TO_SET_NULL, ASSERT_TRUE) {
  server *network = NULL;
  set group = unique_nets_to_set(network, 0);
  EXPECT_TRUE(group.cur_size == 0);
  set_destroy(&group);
  destoy_servers_arr(network);
}

TEST(PRINT_BY_GROUPS_CORRECT, ASSERT_TRUE) {
  server *network = create_servers_arr(2);
  char dns[16] = "server";
  char ip1[16] = "111.111.111.111";
  char ip2[16] = "111.111.111.111";
  char mask[16] = "255.255.255.255";
  int processor = 4;
  int core = 4;
  int success = 1;
  network[0] = server_init(dns, ip1, mask, processor, core, &success);
  network[1] = server_init(dns, ip2, mask, processor, core, &success);
  set group = unique_nets_to_set(network, 2);
  print_by_groups(network, 2, group);
  EXPECT_TRUE(true);
  set_destroy(&group);
  destoy_servers_arr(network);
}


TEST(PRINT_BY_GROUPS_NULL, ASSERT_FALSE) {
  server *network = NULL;
  set group = unique_nets_to_set(network, 1);
  print_by_groups(network, 1, group);
  EXPECT_FALSE(network);
  set_destroy(&group);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
