#include "TestDClassify.h"

TestDClassify::TestDClassify() {
    TEST_ADD(TestDClassify::test_d_align_id);
    TEST_ADD(TestDClassify::test_d_align_score);
    TEST_ADD(TestDClassify::test_d_align_nohit);
}

TestDClassify::~TestDClassify() {}

void TestDClassify::setup() {}

void TestDClassify::tear_down() {}

void TestDClassify::test_d_align_id() {    
    DClassify dc(d_fasta);
    
    pair<int,int> v_part(0,293);
    pair<int,int> j_part(309,364);
    string seq = "CAGGTCCAGCTTGTGCAGTCTGGGGCTGAGGTGAAGAAGCCTGGGGCCTCAGTGAAGGTTTCCTGCAAGGCTTCTGGATACACCTTCACTAGCTATGCTATGCATTGGGTGCGCCAGGCCCCCGGACAAAGGCTTGAGTGGATGGGATGGATCAACGCTGGCAATGGTAACACAAAATATTCACAGAAGTTCCAGGGCAGAGTCACCATTACCAGGGACACATCCGCGAGCACAGCCTACATGGAGCTGAGCAGCCTGAGATCTGAAGACACGGCTGTGTATTACTGTGCGAGAATCATAACTGGTACCCTACTACTACGGTATGGACGTCTGGGGCCAAGGGACCACGGTCACCGTCTCCTCAGGGAGTGCATCCGCCCCAACCCTTTTCCCCCTCGTCTCCTGTGAGAATTCCCCGTCGGATACGAGCAGCGTGGCCGTTGGCTGCCTCGCACAGGACTTCC";
    vector<DLabel> ret_id = dc.classify_d(seq, v_part, j_part);

    TEST_ASSERT(ret_id[0].label == "IGHD1-7*01" || 
		ret_id[0].label == "IGHD1-20*01");
    TEST_ASSERT(ret_id[1].label == "IGHD1-20*01" ||
		ret_id[1].label == "IGHD1-7*01");
}

void TestDClassify::test_d_align_score() {
    DClassify dc(d_fasta);
    
    pair<int,int> v_part(0,293);
    pair<int,int> j_part(309,364);    
    string seq = "CAGGTCCAGCTTGTGCAGTCTGGGGCTGAGGTGAAGAAGCCTGGGGCCTCAGTGAAGGTTTCCTGCAAGGCTTCTGGATACACCTTCACTAGCTATGCTATGCATTGGGTGCGCCAGGCCCCCGGACAAAGGCTTGAGTGGATGGGATGGATCAACGCTGGCAATGGTAACACAAAATATTCACAGAAGTTCCAGGGCAGAGTCACCATTACCAGGGACACATCCGCGAGCACAGCCTACATGGAGCTGAGCAGCCTGAGATCTGAAGACACGGCTGTGTATTACTGTGCGAGAATCATAACTGGTACCCTACTACTACGGTATGGACGTCTGGGGCCAAGGGACCACGGTCACCGTCTCCTCAGGGAGTGCATCCGCCCCAACCCTTTTCCCCCTCGTCTCCTGTGAGAATTCCCCGTCGGATACGAGCAGCGTGGCCGTTGGCTGCCTCGCACAGGACTTCC";
    
    vector<DLabel> ret_v = dc.score_d(seq, v_part, j_part);
    std::sort(ret_v.begin(), ret_v.end(), std::greater<DLabel>());

    TEST_ASSERT(ret_v[0].score == 47);
    TEST_ASSERT(ret_v[0].label == "IGHD1-7*01" ||
		ret_v[0].label == "IGHD1-20*01");
    
    TEST_ASSERT(ret_v[1].score == 47);    
    TEST_ASSERT(ret_v[1].label == "IGHD1-20*01" ||
		ret_v[1].label == "IGHD1-7*01");
}

void TestDClassify::test_d_align_nohit() {
    DClassify dc(d_fasta);
    
    pair<int,int> v_part(1, 301);	
    pair<int,int> j_part(301, 362);
    string seq = "CAGGTGCAGCTGGTGCAGTCTGGGGGAGGCTTGGTAAAGCCTGGGGGGTCCCTTAGACTCTCCTGTGCAGCCTCTGGATTCACTTTCAGTGACGCCTGGATGAGCTGGGTCCGCCAGGCTCCAGGGAAGGGGCTGGAGTGGGTTGGCCGTATTAAAAGCAAAACTGATGGTGGGACAACAGACTACGCTGCACCCGTGAAAGGCGGATTCACCATCTCAAGAGATGATTCAAAAAACACGCTGTATCTGCAAATGAACAGCCTGAAAACCGAGGACACAGCCGTGTATTACTGTGCCGCCCAGACGACGATAGCATCAGCCTTGGACGTCTGGGGCCAAGGGACCACGGTCACCGTCTCCTCA";
    
    std::vector<DLabel> d_lst = dc.classify_d(seq, v_part, j_part);
    TEST_ASSERT(d_lst.size() == 0);
}
