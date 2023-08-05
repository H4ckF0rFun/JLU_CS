#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <immintrin.h>
#include <assert.h>

//#define _FUCK_ARGS

#define bool  int
#define true  1
#define false 0

#define MAX_COUNT    (2000 * 2000 * 3)


#define BLACK	0
#define WHITE	1

#define BOARD_SIZE 8

#pragma GCC target("popcnt")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")


#ifdef _WIN64 
//msvc
#define __inline __inline
#else 
#define __inline __always_inline 
#endif

uint32_t MaxTime = 986999;//398749;//956999;//

typedef struct tagState{
	double 		quality;
	uint32_t 		visit;         		//访问次数
	uint32_t 		len;

	uint64_t 	  	board;
	uint64_t 		coor[2];
	struct tagState* child;      //
	struct tagState* parent;      //
}State;


uint32_t StateTop = 0;
State     State_cache[MAX_COUNT];

__inline State* _state_alloc() {
	return &State_cache[StateTop++];
}


clock_t start_time = 0;
uint32_t me;

/*******************************************debug ***************************************************/

void printBoard(State * state) {
	//printf("0x%llx\n",state->board);

	for(int i = 0;i<64;i++){
		if(!(i&0x7)){
			fprintf(stderr,"\n");
		}

		if(state->board & (1ull << i)){
			int j = 0;

			if(state->coor[me] & (1ull << i)){
				fprintf(stderr,"A ");
			}else if (state->coor[1 - me] & (1ull << i)){
				fprintf(stderr,"B ");
			}else{
				fprintf(stderr,"X ");
			}
		}else{
			fprintf(stderr,"_ ");
		}
	}
	fprintf(stderr,"\n");
}

void showBoard(uint64_t board) {
	for(int i = 0;i<64;i++){
		if(!(i&0x7)){
			putchar('\n');
		}

		if(board & (1ull << i)){	
			printf("X ");
		}else{
			printf("_ ");
		}
	}
	puts("");
}

/****************************************evalution engine*********************************************/



#define min(x,y) ((x) < (y) ? (x) : (y))


__attribute__((aligned(32))) uint64_t king_move_me[64];
__attribute__((aligned(32))) uint64_t king_move_you[64];
__attribute__((aligned(32))) uint64_t queen_move_me[64];
__attribute__((aligned(32))) uint64_t queen_move_you[64];

uint8_t king_move_me_max_dist;
uint8_t king_move_you_max_dist;
uint8_t queen_move_me_max_dist;
uint8_t queen_move_you_max_dist;

uint32_t _debug_evaluate_count = 0;
uint32_t _dup_count = 0;


double args[28][6] = {
		{ 0.07747249543793637 ,0.05755603330699520 ,0.64627749023334498 ,0.70431267004292740 ,0.02438131097879579 , 0.00 },
		{ 0.05093047840251742 ,0.06276538622537013 ,0.69898059004821581 ,0.66192728970497727 ,0.02362598306372760 , 0.00 },
		{ 0.06036622274224539 ,0.06253298199478051 ,0.60094570235521628 ,0.67719126081076242 ,0.01873142786640421 , 0.00 },
		{ 0.07597341130849308 ,0.06952095866594065 ,0.69061184234845333 ,0.67989394578528273 ,0.02098781856298665 , 0.00 },
		{ 0.08083391263897154 ,0.08815144960484271 ,0.58981849824874917 ,0.54664183543259470 ,0.02318479501373763 , 0.00 },
		{ 0.09155731347030857 ,0.08397548702353251 ,0.56392480085083986 ,0.54319242129550227 ,0.02317401477849946 , 0.00 },
		{ 0.10653095458609237 ,0.10479793630859575 ,0.54840938009286515 ,0.53023658889860381 ,0.02084758939889652 , 0.00 },
		{ 0.11534143744086589 ,0.11515706838023705 ,0.53325566869906469 ,0.52423368303553451 ,0.02237127451593010 , 0.00 },
		{ 0.12943854523554690 ,0.12673742164114844 ,0.50841519367287034 ,0.52208373964502879 ,0.02490545306630711 , 0.00 },
		{ 0.12882484162931859 ,0.13946973532382280 ,0.49621839819987758 ,0.51776460089353364 ,0.03045473763611049 , 0.00 },
		{ 0.13701233819832731 ,0.15338865590616042 ,0.47601466399954588 ,0.51500429509193190 ,0.03249896738636078 , 0.00 },
		{ 0.14530543898518938 ,0.15565237403332051 ,0.45365475320199057 ,0.50934623406618500 ,0.03830491784046246 , 0.00 },
		{ 0.14521045986025419 ,0.16388365022083374 ,0.44531995327608060 ,0.50517597255948953 ,0.04864124027084386 , 0.00 },
		{ 0.13750613208150655 ,0.16326621164859418 ,0.43619350878439399 ,0.50328876650721398 ,0.05912794240603884 , 0.00 },
		{ 0.13565263325548560 ,0.15529175902376631 ,0.42382223063419649 ,0.50288212924827379 ,0.07437679521343679 , 0.00 },
		{ 0.12382760525087406 ,0.10361944098637088 ,0.50487335391408680 ,0.55808747967333505 ,0.02791980213792046 , 0.00 },
		{ 0.11809487853625075 ,0.14632850080535232 ,0.40738388113193924 ,0.41782129616811122 ,0.10308050317730764 , 0.00 },
		{ 0.10805473551960752 ,0.15043981450391137 ,0.40520488356004784 ,0.43073574707030956 ,0.10967613304465569 , 0.00 },
		{ 0.09668240983912251 ,0.15666221434557865 ,0.40215634987047013 ,0.44165716517577754 ,0.10906426061069142 , 0.00 },
		{ 0.10585263971502025 ,0.16319090506614549 ,0.38220029690800922 ,0.45465487463858675 ,0.10062997439277618 , 0.00 },
		{ 0.11123671989551248 ,0.15516074827095279 ,0.36904588744714037 ,0.46534418781939937 ,0.09118229977179015 , 0.00 },
		{ 0.12535649823409767 ,0.10492555251930048 ,0.35567115915540981 ,0.48043579160677637 ,0.08337580273275977 , 0.00 },
		{ 0.28657326967317970 ,0.16655279311197080 ,0.38060545469477008 ,0.42472577515072628 ,0.10316994796202342 , 0.00 },
		{ 0.07143084940040888 ,0.16655279311197080 ,0.36658063304313299 ,0.39520049916162908 ,0.02194263694320541 , 0.00 },
		{ 0.07143084940040888 ,0.16655279311197080 ,0.36658063304313299 ,0.39520049916162908 ,0.02194263694320541 , 0.00 },
		{ 0.07143084940040888 ,0.16655279311197080 ,0.36658063304313299 ,0.39520049916162908 ,0.02194263694320541 , 0.00 },
		{ 0.07143084940040888 ,0.16655279311197080 ,0.36658063304313299 ,0.39520049916162908 ,0.02194263694320541 , 0.00 },
		{ 0.07143084940040888 ,0.14627749023334498 ,0.36658063304313299 ,0.39520049916162908 ,0.02194263694320541 , 0.00 }
};



__inline void king_move_bfs_avx2(State * state,uint64_t board,uint64_t coor,uint64_t* can_moves,uint8_t * max_dist){
	uint8_t  dist = 0;
	uint64_t last_can = coor;
	uint64_t can;
	board = ~board;
	can_moves[dist++] = coor;
	//showBoard(coor);

	__m256i d0_mask = _mm256_set_epi64x(
						0xfefefefefefefefe,
						0x7f7f7f7f7f7f7f7f,
						0xffffffffffffffff,
						0xfefefefefefefefe);
	__m256i d1_mask = _mm256_set_epi64x(
						0x7f7f7f7f7f7f7f7f,
						0xfefefefefefefefe,
						0xffffffffffffffff,
						0x7f7f7f7f7f7f7f7f);
	__m256i count   = _mm256_set_epi64x(1,7,8,9);

	for(;;){
		__m256i _pos = _mm256_set1_epi64x(can_moves[dist-1]);
		__m256i _can = _mm256_or_si256(
			_mm256_or_si256(
				_mm256_srlv_epi64(_mm256_and_si256(_pos,d0_mask),count),
				_mm256_sllv_epi64(_mm256_and_si256(_pos,d1_mask),count)	
			),
			_pos
		);

		can = ( 
				_mm256_extract_epi64(_can,0) | 
				_mm256_extract_epi64(_can,1) |
				_mm256_extract_epi64(_can,2) |  
				_mm256_extract_epi64(_can,3) 
			) & board;  //找出可以走的,而且要和距离为dist - 1的不一样.

		if(can == last_can){
			break;
		}
		last_can = can;
		can_moves[dist++] = can;
	}

	for(int i = dist - 1;i > 1;i--){
		can_moves[i] ^= can_moves[i-1];
	}
	*max_dist = dist;
}

__inline void queen_move_bfs_avx2(uint64_t board,uint64_t coor,uint64_t* can_moves,uint8_t * max_dist){
	uint8_t  dist = 0;
	uint64_t can;
	uint64_t last_can = coor;

	board = ~board;
	can_moves[dist++] = coor;

	__m256i d0_mask = _mm256_set_epi64x(
												0xfefefefefefefefe,
												0x7f7f7f7f7f7f7f7f,
												0xffffffffffffffff,
												0xfefefefefefefefe);

	__m256i d1_mask = _mm256_set_epi64x(
												0x7f7f7f7f7f7f7f7f,
												0xfefefefefefefefe,
												0xffffffffffffffff,
												0x7f7f7f7f7f7f7f7f);

	__m256i count = _mm256_set_epi64x(1,7,8,9);
	__m256i and_mask = _mm256_set1_epi64x(board);

	for(;;){
		__m256i _d0_pos[8],_d1_pos[8],_can;
		
		can = 0;
		_d0_pos[0] = _mm256_set1_epi64x(can_moves[dist-1]);
		_d1_pos[0] = _mm256_set1_epi64x(can_moves[dist-1]);
			//走七步.把每一步能到达的位置放到 pos数组中。
			for(int i = 1 ; i<=7;i++){
				_d0_pos[i] = _mm256_and_si256(_mm256_srlv_epi64(_mm256_and_si256(_d0_pos[i - 1],d0_mask),count),and_mask);
				_d1_pos[i] = _mm256_and_si256(_mm256_sllv_epi64(_mm256_and_si256(_d1_pos[i - 1],d1_mask),count),and_mask);
			}
			//_can里面是包括上一步走的距离的.
			_can = _mm256_or_si256(
					_mm256_or_si256(
						_mm256_or_si256(
							_mm256_or_si256(_d0_pos[0],_d0_pos[1]),
							_mm256_or_si256(_d0_pos[2],_d0_pos[3])
						),
					
						_mm256_or_si256(
							_mm256_or_si256(_d0_pos[4],_d0_pos[5]),
							_mm256_or_si256(_d0_pos[6],_d0_pos[7])
						)
					),
					_mm256_or_si256(
						_mm256_or_si256(
							_mm256_or_si256(_d1_pos[0],_d1_pos[1]),
							_mm256_or_si256(_d1_pos[2],_d1_pos[3])
						),
						_mm256_or_si256(
							_mm256_or_si256(_d1_pos[4],_d1_pos[5]),
							_mm256_or_si256(_d1_pos[6],_d1_pos[7])
						)
					)
				);

			can = ( 
					_mm256_extract_epi64(_can,0) | 
					_mm256_extract_epi64(_can,1) |
					_mm256_extract_epi64(_can,2) |  
					_mm256_extract_epi64(_can,3) 
				) & board;  //找出可以走的,而且要和距离为dist - 1的不一样.
			
			// puts("===================================");
			// showBoard(last_can);
			// showBoard(can);

			if(can == last_can){
				break;
			}
			last_can = can;
			can_moves[dist++] = can;
	}
	
	for(int i = dist - 1;i > 1;i--){
		can_moves[i] ^= can_moves[i-1];
	}
	*max_dist = dist;
}

//不需要保存,瓶颈在读写内存.
//queen一次能走到的位置,

__inline double calc_mobility_avx2(uint64_t board ,uint64_t coor){
	//如何计算出一步queen的king距离.
	//king 距离没办法计算,只能一步一步走.
	board = ~ board;
	double m = 0;
	uint64_t u64_can;

	__m256i d0_mask = _mm256_set_epi64x(
								0xfefefefefefefefe,
								0x7f7f7f7f7f7f7f7f,
								0xffffffffffffffff,
								0xfefefefefefefefe);
	__m256i d1_mask = _mm256_set_epi64x(
								0x7f7f7f7f7f7f7f7f,
								0xfefefefefefefefe,
								0xffffffffffffffff,
								0x7f7f7f7f7f7f7f7f);

	__m256i count = _mm256_set_epi64x(1,7,8,9);
	__m256i and_mask = _mm256_set1_epi64x(board);

	__m256i  _d0_pos,_d1_pos;

	_d0_pos = _d1_pos = _mm256_set1_epi64x(coor);

	//uint64_t visited = 0;

	for(int i = 1 ; i<=7;i++){
		//朝着八个方向走一步.
		_d0_pos = _mm256_and_si256(_mm256_srlv_epi64(_mm256_and_si256(_d0_pos,d0_mask),count),and_mask);
		_d1_pos = _mm256_and_si256(_mm256_sllv_epi64(_mm256_and_si256(_d1_pos,d1_mask),count),and_mask);
		//
		__m256i _can = _mm256_or_si256(_d0_pos,_d1_pos);
		//走一步能走到的位置
		uint64_t u64_can =  _mm256_extract_epi64(_can,0) | 
							_mm256_extract_epi64(_can,1) |
							_mm256_extract_epi64(_can,2) |
							_mm256_extract_epi64(_can,3);

		__m256i space = _mm256_or_si256(
			_mm256_and_si256(_mm256_srlv_epi64(_mm256_and_si256(_mm256_set1_epi64x(u64_can),d0_mask),count),and_mask),
			_mm256_and_si256(_mm256_sllv_epi64(_mm256_and_si256(_mm256_set1_epi64x(u64_can),d0_mask),count),and_mask)
		);

		//visited |= u64_can;
		//这个计算会把公共的部分算成一个。不过无所谓应该.
		uint64_t u64Space = (
				_mm256_extract_epi64(space,0) |
				_mm256_extract_epi64(space,1) |
				_mm256_extract_epi64(space,2) |
				_mm256_extract_epi64(space,3)
		);
		m +=  __builtin_popcountll(u64Space) / ( i * 1.0 );
	};
	//showBoard(coor);
	//showBoard(visited);
	return m;
}



//这个也不需要表格.

/*
	position1 = 2 * sum(2 ^ D(me,queen) - 2 ^ D(you,queen))
			  = 2 * (sum ( 2 ^ D_A(me,queen)) - sum (2 ^ D_A(you,queen)))
		 	如果 A 是有一方无法到达的话,那么2 ^ (-x )是0.可以直接忽略。
			所以直接计算出me能到达的位置 - you能到达的位置即可.
*/

__inline double calc_queen_position(uint64_t * can_moves_arr_me,uint8_t me_len,
						   uint64_t * can_moves_arr_you,uint8_t you_len){
	double ret = 0,f_pow;
	uint64_t can,off,_pow;

	for(int i = 1;i<me_len;i++){
		can = can_moves_arr_me[i];
		off = i;
		_pow = 0x3ff0000000000000ull - (off << 52);
		f_pow = *(double*)&_pow;
		ret += __builtin_popcountll(can) * f_pow;
	}

	for(int i = 1;i<you_len;i++){
		can = can_moves_arr_you[i];
		off = i;
		_pow = 0x3ff0000000000000ull - (off << 52);
		f_pow = *(double*)&_pow;
		ret -= __builtin_popcountll(can) * f_pow;
	}
	return 2 * ret;
}


//这个呢.....king position不太好计算...
//1 <= (2 ^ D_king(A) - 2 ^ D_king(A)) / 6 <= 1 
//简化一下，取消minmax

__inline double calc_king_position(uint64_t * can_moves_arr_me,uint8_t me_len,
						   uint64_t * can_moves_arr_you,uint8_t you_len){
	//只有大于等于6的能是1.
	//统计一下能走的位置顺便，防止对手围住很多,
	double p = 0;
	for(int i = 1; i < me_len ;i++){
		p -= __builtin_popcountll(can_moves_arr_me[i]) * i / 6.0;
		p += __builtin_popcountll(can_moves_arr_me[i]);
	}
	for(int i = 1;i < you_len ;i++){
		p += __builtin_popcountll(can_moves_arr_you[i]) * i / 6.0;
		p -= __builtin_popcountll(can_moves_arr_you[i]);
	}
	return p;			//....这个反了....应该是 you - me..
}


__inline int32_t calc_territory_fast(uint64_t * can_moves_arr_me,uint8_t me_len,
						   uint64_t * can_moves_arr_you,uint8_t you_len){
	int32_t t = 0;
	uint64_t visited = 0;

	for(int i = 1 ;i < me_len && i < you_len;i++){
		//printf("%ull ,%ull \n",diff & can_moves_arr_me[i],diff & can_moves_arr_you[i]);
		t += __builtin_popcountll(can_moves_arr_me[i] & (~visited));
		t -= __builtin_popcountll(can_moves_arr_you[i] & (~visited));
		visited |= can_moves_arr_me[i] | can_moves_arr_you[i];
	}
	////
	for(int i = me_len ;i < you_len;i++){
		t -= __builtin_popcountll(can_moves_arr_you[i]  & (~visited));
		visited |= can_moves_arr_you[i]; 
	}

	for(int i = you_len;i < me_len;i++){
		t += __builtin_popcountll(can_moves_arr_me[i]  & (~visited));
		visited |= can_moves_arr_me[i]; 
	}
	return t;
}


__inline bool timeout() {
	return (((clock() - start_time)) > MaxTime);
}



__inline double evaluate(State* state) {
	uint64_t board = state->board;

	++_debug_evaluate_count;

	double score = 0.0, t1 = 0, t2 = 0, p1 = 0, p2 = 0, m0 = 0,m1 = 0;
	king_move_bfs_avx2(state,board,state->coor[me],king_move_me,&king_move_me_max_dist) ;
	king_move_bfs_avx2(state,board,state->coor[1 - me],king_move_you,&king_move_you_max_dist) ;

	queen_move_bfs_avx2(board,state->coor[me],queen_move_me,&queen_move_me_max_dist) ;
	queen_move_bfs_avx2(board,state->coor[1 - me],queen_move_you,&queen_move_you_max_dist) ;


	t1 = calc_territory_fast(queen_move_me,queen_move_me_max_dist,queen_move_you,queen_move_you_max_dist);
	t2 = calc_territory_fast(king_move_me,king_move_me_max_dist,king_move_you,king_move_you_max_dist);


	p1 = calc_queen_position(queen_move_me,queen_move_me_max_dist,queen_move_you,queen_move_you_max_dist);
	p2 = calc_king_position(king_move_me,king_move_me_max_dist,king_move_you,king_move_you_max_dist);

	m0 = calc_mobility_avx2(board,state->coor[me]) - calc_mobility_avx2(board,state->coor[1-me]);
	//}
    //printf("%lf %lf %lf %lf %lf %lf\n",t1,t2,p1,p2,m0,m1);

	uint32_t evaluate_turn = (__builtin_popcountll(state->board) - 8) >> 1;

	score = (
			args[evaluate_turn][0] * t1 + 
			args[evaluate_turn][1] * t2 +
			args[evaluate_turn][2] * p1 + 
			args[evaluate_turn][3] * p2 +
			args[evaluate_turn][4] * m0) * 0.20;		//y = -0.04x + 1.04
			
	return 1 / (1 + exp(-score));
}


__inline uint64_t get_queen_can_moves_avx2(uint64_t board,uint64_t coor){
	__m256i _d0_pos,_d1_pos,_can = {0};
	uint64_t	can;

	register __m256i d0_mask = _mm256_set_epi64x(
								0xfefefefefefefefe,
								0x7f7f7f7f7f7f7f7f,
								0xffffffffffffffff,
								0xfefefefefefefefe);
	register __m256i d1_mask = _mm256_set_epi64x(
								0x7f7f7f7f7f7f7f7f,
								0xfefefefefefefefe,
								0xffffffffffffffff,
								0x7f7f7f7f7f7f7f7f);

	register __m256i count = _mm256_set_epi64x(1,7,8,9);
	register __m256i and_mask = _mm256_set1_epi64x(board);

	
	_d0_pos = _d1_pos =_mm256_set1_epi64x(coor);
		//走七步.
	for(int i = 1 ; i<=7;i++){
		_d0_pos = _mm256_and_si256(_mm256_srlv_epi64(_mm256_and_si256(_d0_pos,d0_mask),count),and_mask);
		_d1_pos = _mm256_and_si256(_mm256_sllv_epi64(_mm256_and_si256(_d1_pos,d1_mask),count),and_mask);

		_can = _mm256_or_si256(
				_mm256_or_si256(_d0_pos,_d1_pos),
				_can
		);
	}
	can = ( 
			_mm256_extract_epi64(_can,0) | 
			_mm256_extract_epi64(_can,1) |
			_mm256_extract_epi64(_can,2) |  
			_mm256_extract_epi64(_can,3) 
		) & board; 
	
	return can;
}

//能否一次直接求出四个棋能走的位置.
__inline void generate_moves(State* state, int turn) {
	uint64_t b0 = state->board;
	uint64_t chess;
	State * l = NULL;
	uint64_t gen_count = 0;

	chess =  state->coor[turn];

	for (;chess;) {
		uint64_t chess_coor = chess & (-chess);
		uint64_t can_moves = 0;
		chess ^= chess_coor;

		/* 遇到障碍物就停止,所以每走一步就要和board and 一次 */
		can_moves = get_queen_can_moves_avx2(~b0,chess_coor);

		//枚举能走的位置.
		for (;can_moves;){
			uint64_t new_pos = can_moves & (-can_moves);					//最低为的1
			can_moves ^= new_pos;											//取消标记.
			b0 ^= (new_pos ^ chess_coor);									//取走棋子,放到新的位置

			//计算arrow 能放到哪些位置.
			uint64_t arrow_can = 0;
			arrow_can = get_queen_can_moves_avx2(~b0,new_pos);

			for(;arrow_can;){
				uint64_t arrow_pos = arrow_can & (-arrow_can);
				arrow_can -= arrow_pos;
				b0 ^=  arrow_pos;					//把arrow 放到board 上	

				State * new_state = _state_alloc();
				++gen_count;

				if(__glibc_unlikely(l == NULL))		//只有第一次才会是NULL
					l = new_state;

				new_state->board = b0;
				new_state->coor[0] = state->coor[0];
				new_state->coor[1] = state->coor[1];
				new_state->coor[turn] ^= (new_pos ^ chess_coor);
				new_state->parent = state;
				new_state->quality = (me == turn) ? evaluate(new_state) : 1 - evaluate(new_state);

				b0 ^= (arrow_pos);
			}
			b0 ^= (new_pos ^ chess_coor);									//取走棋子,放到旧的位置.
		}
	}

	state->len = gen_count;
	state->child = l;
}


/*
	这里的Q用价值代替。N 是为了防止select 的时候遇到除0的情况。
	Q / (1 + N) + c * sqrt(ln(Np) / (1 + n))....
*/

double C;

uint64_t debug_uct_count = 0;
__inline double UCT(State* state){
	++debug_uct_count;
    return state->quality / (1 + state->visit) +
     C *  __builtin_sqrt( __builtin_log(state->parent->visit) / (1 + state->visit));
}

#define LOG_POLY_DEGREE 6

/*
log2 计算.
http://jrfonseca.blogspot.com/2008/09/fast-sse2-pow-tables-or-polynomials.html


*/
#define POLY0(x, c0) _mm_set1_ps(c0)
#define POLY1(x, c0, c1) _mm_add_ps(_mm_mul_ps(POLY0(x, c1), x), _mm_set1_ps(c0))
#define POLY2(x, c0, c1, c2) _mm_add_ps(_mm_mul_ps(POLY1(x, c1, c2), x), _mm_set1_ps(c0))
#define POLY3(x, c0, c1, c2, c3) _mm_add_ps(_mm_mul_ps(POLY2(x, c1, c2, c3), x), _mm_set1_ps(c0))
#define POLY4(x, c0, c1, c2, c3, c4) _mm_add_ps(_mm_mul_ps(POLY3(x, c1, c2, c3, c4), x), _mm_set1_ps(c0))
#define POLY5(x, c0, c1, c2, c3, c4, c5) _mm_add_ps(_mm_mul_ps(POLY4(x, c1, c2, c3, c4, c5), x), _mm_set1_ps(c0))


__m128 log2f4(__m128 x)
{
   __m128i exp = _mm_set1_epi32(0x7F800000);
   __m128i mant = _mm_set1_epi32(0x007FFFFF);
   __m128 one = _mm_set1_ps( 1.0f);
   __m128i i = _mm_castps_si128(x);
   __m128 e = _mm_cvtepi32_ps(_mm_sub_epi32(_mm_srli_epi32(_mm_and_si128(i, exp), 23), _mm_set1_epi32(127)));
   __m128 m = _mm_or_ps(_mm_castsi128_ps(_mm_and_si128(i, mant)), one);
   __m128 p;

   /* Minimax polynomial fit of log2(x)/(x - 1), for x in range [1, 2[ */
#if LOG_POLY_DEGREE == 6
   p = POLY5( m, 3.1157899f, -3.3241990f, 2.5988452f, -1.2315303f,  3.1821337e-1f, -3.4436006e-2f);
#elif LOG_POLY_DEGREE == 5
   p = POLY4(m, 2.8882704548164776201f, -2.52074962577807006663f, 1.48116647521213171641f, -0.465725644288844778798f, 0.0596515482674574969533f);
#elif LOG_POLY_DEGREE == 4
   p = POLY3(m, 2.61761038894603480148f, -1.75647175389045657003f, 0.688243882994381274313f, -0.107254423828329604454f);
#elif LOG_POLY_DEGREE == 3
   p = POLY2(m, 2.28330284476918490682f, -1.04913055217340124191f, 0.204446009836232697516f);
#else
#error
#endif
   /* This effectively increases the polynomial degree by one, but ensures that log2(1) == 0*/
   p = _mm_mul_ps(p, _mm_sub_ps(m, one));
   return _mm_add_ps(p, e);
}
//近似计算ln 函数.
__m256d ln(uint32_t v0,uint32_t v1,uint32_t v2,uint32_t v3){
    return _mm256_cvtps_pd(
        _mm_div_ps(
            log2f4(_mm_cvtepi32_ps(_mm_set_epi32(v0,v1,v2,v3))),
            log2f4(_mm_set1_ps(2.718281828459045))
        )
    );
}


__inline State * get_uct_max_state(State* c,int64_t len){
	__m256d max_uct = {0};
	__m256d max_addr = {0};
	double _max_uct = 0;
	State * _max_state = NULL;
	double ucts[4];

	for(;len >= 4;len -= 4){
		__m256d den = _mm256_cvtepi32_pd(_mm_add_epi32(
					_mm_set_epi32(c[0].visit,c[1].visit,c[2].visit,c[3].visit),
					_mm_set1_epi32(1)
				)
			);
		__m256d cur_value = _mm256_add_pd(
			_mm256_div_pd(
				_mm256_set_pd(c[0].quality,c[1].quality,c[2].quality,c[3].quality),
				den
			)
			,
			_mm256_mul_pd(
				_mm256_set1_pd(C) ,
				_mm256_sqrt_pd(
					_mm256_div_pd(
						ln(c[0].parent->visit,c[1].parent->visit,c[2].parent->visit,c[3].parent->visit),				
						den
					)
				)
			)
		);
		__m256d cur_addr = _mm256_castsi256_pd(_mm256_set_epi64x((uint64_t)c,(uint64_t)(c + 1),(uint64_t)(c + 2),(uint64_t)(c + 3)));
		__m256d mask = _mm256_cmp_pd(cur_value,max_uct,_CMP_GT_OQ);		//如果成立,对应的八个字节都是1

		max_uct = _mm256_blendv_pd(max_uct,cur_value,mask);
		max_addr = _mm256_blendv_pd(max_addr,cur_addr,mask);

		c += 4;
	}
	
	_mm256_storeu_pd(ucts,max_uct);

	if(ucts[0] > _max_uct){
		_max_uct = ucts[0];
		_max_state = (State*)_mm256_extract_epi64(_mm256_castpd_si256(max_addr),0);
	}
	if(ucts[1] > _max_uct){
		_max_uct = ucts[1];
		_max_state = (State*)_mm256_extract_epi64(_mm256_castpd_si256(max_addr),1);
	}
	if(ucts[2] > _max_uct){
		_max_uct = ucts[2];
		_max_state = (State*)_mm256_extract_epi64(_mm256_castpd_si256(max_addr),2);
	}
	if(ucts[3] > _max_uct){
		_max_uct = ucts[3];
		_max_state = (State*)_mm256_extract_epi64(_mm256_castpd_si256(max_addr),3);
	}
	while(len > 0){
		double _uct = UCT(c);
		if(_uct >= _max_uct){
			_max_uct = _uct;
			_max_state = c;
		}
		c++;
		--len;
	}
	return _max_state;
}	


__inline void expand(State* state,int next_turn){
	if(state->coor[0] != 0xffffffffffffffff){
		generate_moves(state,next_turn);

		if(state->child == NULL){							//next turn 走不了了.
			state->child = _state_alloc();
			state->len = 1;
			
			state->child->coor[0] = 0xffffffffffffffff;
			state->child->parent = state;
			state->child->quality = 0;						//这个节点的价值是0
		}
	}
}


__inline State* select(State * leaf,int* next_turn){
    while(leaf->child){
		leaf = get_uct_max_state(leaf->child,leaf->len);
		*next_turn = 1 - *next_turn;
    }
    return leaf;
}

/*
15
-1 -1 -1 -1 -1 -1
5 0 5 6 4 7
2 7 2 2 1 3
0 2 0 4 6 4
5 7 3 5 3 0
0 4 1 5 0 6
0 5 5 0 0 5
7 2 5 2 3 2
5 0 5 1 6 1
2 0 1 1 1 2
3 5 2 5 2 6
5 2 5 3 7 3
7 5 6 6 4 4
1 5 1 6 1 4
2 2 2 0 2 2
5 3 5 2 4 2
2 0 0 0 0 2
5 2 6 3 3 6
0 0 1 0 2 1
5 6 4 6 2 4
6 6 5 6 5 3
6 3 7 2 7 0
5 1 6 2 6 3
7 2 7 1 7 2
6 2 5 1 6 0
7 1 6 2 7 1
5 1 5 2 5 1
4 6 5 7 4 6
5 6 6 6 5 6


*/

void printTree(State* root,int who){
	fprintf(stderr,"[State: %p ,visit: %d ,who: %d,quality: %lf]\n",
		root,root->visit,who,root->quality);
	fprintf(stderr,"==========================\n");
	int l = root->len;
	State * c = root->child;

	for(int i = 0;i < l;i++){
		printTree(c,1 - who);
		c++;
	}
}

__inline void backup(State * state,int *next_turn){
	double value = state->quality;
	State * temp = state;

	state->visit++;
	state = state->parent;
	value = 1 - value;
	
    while(state){
        state->visit++;
		state->quality += value;

		state = state->parent;
		value = 1 - value;
    }
}


__inline void MCTS(State*root){
    State*leaf,*action = NULL;
	uint64_t diff;
	uint8_t start,result,arrow;
	uint32_t max_visit;
	int next_turn,iteration = 0;
	double max_score;

	start_time = clock();

    for(;!timeout();){
	//for(int i = 0;i<121483;i++){
		next_turn	= me;
        leaf 		= select(root,&next_turn);

		if(leaf->visit){							//score 一直在变小..所以归一之后也在一直变小.........
			expand(leaf,next_turn);					//最后的输赢要怎么算??????
			leaf  = select(leaf,&next_turn);
		}
		backup(leaf,&next_turn);
		iteration++;
    }

	//用最大访问次数
	State * c = root->child;
	for(int i = 0;i < root->len;i++,c++){
		// diff = root->coor[me] ^ c->coor[me];
		// start = __builtin_ctzll(root->coor[me] & diff);
		// result = __builtin_ctzll(c->coor[me] & diff);
		// arrow = __builtin_ctzll(root->board ^ diff ^ c->board);

		// if(c->visit){
		// 	printf("action: %d %d %d %d %d %d ,",
		// 		start & 0x7,
		// 		start >> 3,

		// 		result & 0x7,
		// 		result >> 3,

		// 		arrow & 0x7,
		// 		arrow >> 3
		// 	);
		// 	printf("parent_visit: %d ,visit: %d ,quality: %lf ,UCT:%.10lf\n ",c->parent->visit,c->visit,c->quality,UCT(c));
		// }

		if(action == NULL || c->visit > max_visit){
			max_visit = c->visit;
			action = c;
		}
	}
	diff = root->coor[me] ^ action->coor[me];
	start = __builtin_ctzll(root->coor[me] & diff);
	result = __builtin_ctzll(action->coor[me] & diff);
	arrow = __builtin_ctzll(root->board ^ diff ^ action->board);

	//printTree(root,1 - me);

	printf("%d %d %d %d %d %d\n",
		start & 0x7,
		start >> 3,

		result & 0x7,
		result >> 3,

		arrow & 0x7,
		arrow >> 3
	);
	/*
	服务器:
	5 7 5 2 6 3
	elapse: 1.914058,iterator: 54042,evaluate: 2298314, failed: 0
	
	本地:
	iterator: 129745,evaluate: 4802809
	*/
	printf("elapse: %lf,",(clock() - start_time) * 1.0 / CLOCKS_PER_SEC);
	printf("iterator: %d,",iteration);
	printf("evaluate: %d, ",_debug_evaluate_count);
	printf("call_uct_count: %llu \n",debug_uct_count);
}

/**************************************read board *****************************************/

// 在坐标处落子，检查是否合法或模拟落子
void move(State* state,int x0, int y0, int x1, int y1, int x2, int y2, int who)
{
	assert(0 == ((~0x7) & (x0 |x1 |x2 | y0 | y1| y2)));
	state->board ^= (1ull << ((y0 << 3) | x0 )) ^ (1ull << ((y1 << 3) | x1 )) ^ (1ull << ((y2 << 3) | x2 ));
	state->coor[who] ^= (1ull << ((y0 << 3) | x0 )) ^ (1ull << ((y1 << 3) | x1 )) ;
}


int main(int argc,char * argv[])
{
	State input_state = { 0 };
	// 初始化棋盘
	int turnID;

	input_state.board |= (1ull << 2) | (1ull << 5) | (1ull << 16) | (1ull << 23);
	input_state.coor[BLACK] = input_state.board;

	input_state.board |= (1ull << 40) | (1ull << 47) | (1ull << 58) | (1ull << 61);
	input_state.coor[WHITE] = input_state.board ^ input_state.coor[BLACK];

	scanf("%d", &turnID);
	me = WHITE;

	if(turnID == 1)
		MaxTime <<= 1;

	for(int i = 0;i<turnID;i++){
		int x0, y0, x1, y1, x2, y2;
		scanf("%d%d%d%d%d%d", &x0, &y0, &x1, &y1, &x2, &y2);
		if (x0 == -1)
			me = BLACK; // 第一回合收到坐标是-1, -1，说明我是黑方
		else
			move(&input_state,x0, y0, x1, y1, x2, y2, 1 - me); // 模拟对方落子

		if (i < turnID - 1) {
			scanf("%d%d%d%d%d%d", &x0, &y0, &x1, &y1, &x2, &y2);
			if (x0 >= 0)
				move(&input_state,x0, y0, x1, y1, x2, y2, me); // 模拟己方落子
		}
	}

	C = 0.176999999999 * exp(-0.008  * (turnID - 1.41));
	//printBoard(&input_state);
	MCTS(&input_state);
	return 0;
}

