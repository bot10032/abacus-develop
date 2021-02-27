#ifndef EXX_ABFS_PARALLEL_COMMUNICATE_DM3_H
#define EXX_ABFS_PARALLEL_COMMUNICATE_DM3_H

#include "src_ri/exx_abfs-parallel.h"
#include "src_ri/abfs-vector3_order.h"

#include <vector>
#include <map>
#include <set>
#include <memory>

using namespace std;

class Exx_Abfs::Parallel::Communicate::DM3
{
public:
	void cal_DM(const double threshold_D);

	vector<map<size_t,map<size_t,map<Abfs::Vector3_Order<int>,matrix>>>> DMr;

private:
	template<typename Tmatrix> vector<map<size_t,map<size_t,map<Abfs::Vector3_Order<int>,matrix>>>>
		K_to_R(const vector<Tmatrix> &DK_2D, const double threshold_D) const;
	const matrix &D_phase( const matrix &DK, const int ik, const Abfs::Vector3_Order<int> &box2) const;	
	matrix D_phase( const ComplexMatrix &DK, const int ik, const Abfs::Vector3_Order<int> &box2) const;	
//	vector<map<size_t,map<size_t,map<Abfs::Vector3_Order<int>,matrix>>>>
//		allreduce(const vector<map<size_t,map<size_t,map<Abfs::Vector3_Order<int>,matrix>>>> &DR_a2D);

	class Allreduce
	{
		public:
			void init(
				const MPI_Comm &mpi_comm_in,
				const map<set<size_t>,set<size_t>> &H_atom_pairs_group);
			vector<map<size_t,map<size_t,map<Abfs::Vector3_Order<int>,matrix>>>> a2D_to_exx(
				vector<map<size_t,map<size_t,map<Abfs::Vector3_Order<int>,matrix>>>> &data_local) const;

		private:
			vector<map<size_t,set<size_t>>> H_atom_pairs_group_rank;	//H_atom_pairs_group_rank[rank][iat1][iat2]
			vector<size_t> send_size_list;
			size_t recv_size;

			MPI_Comm mpi_comm;
			int comm_sz;
			int my_rank;

			enum class Flag_Send {undo, begin_oar, finish_oar, begin_isend, finish_isend};
			enum class Flag_Recv {undo, begin_irecv, begin_iar, finish_iar};

			//vector<pair<bool,bool>> get_atom_in_2D() const;
			vector<map<size_t,set<size_t>>> get_H_atom_pairs_group_rank(
				const map<set<size_t>,set<size_t>> &H_atom_pairs_group) const;
			void get_send_recv_size(
				const vector<map<size_t,set<size_t>>> &H_atom_pairs_group_rank,
				const map<set<size_t>,set<size_t>> &H_atom_pairs_group,
				vector<size_t> &send_size_list, size_t &recv_size) const;
			void init_flags(
				vector<atomic<Flag_Send>> &flags_send,
				vector<atomic<Flag_Recv>> &flags_recv) const;
			bool finish_judge(
				const vector<atomic<Flag_Send>> &flags_send,
				const vector<atomic<Flag_Recv>> &flags_recv) const;
			bool memory_enough(
				const int rank_send_next,
				const vector<atomic<Flag_Send>> &flags_send) const;
			void send_data_process(
				const int rank_send_now,
				const vector<map<size_t,map<size_t,map<Abfs::Vector3_Order<int>,matrix>>>> &data_local,
				vector<vector<double>> &oarps_isend,
				vector<atomic<Flag_Send>> &flags_send) const;
			vector<map<size_t,map<size_t,map<Abfs::Vector3_Order<int>,matrix*>>>> get_intersection(
				const int rank_send_now,
				vector<map<size_t,map<size_t,map<Abfs::Vector3_Order<int>,matrix>>>> &data_local) const;				
			void recv_data_process(
				const int rank_recv,
				vector<map<size_t,map<size_t,map<Abfs::Vector3_Order<int>,matrix>>>> &data_all,
				vector<vector<double>> &iarps_irecv,
				vector<atomic<Flag_Recv>> &flags_recv,
				atomic_flag &lock_insert) const;
			template<typename M> void insert_data(
				vector<map<size_t,map<size_t,map<Abfs::Vector3_Order<int>,M>>>> &data_rank,
				vector<map<size_t,map<size_t,map<Abfs::Vector3_Order<int>,matrix>>>> &data_all) const;
			matrix& get_matrix(matrix&m) const;
			matrix& get_matrix(matrix*pm) const;
	};

public:
	Allreduce allreduce;
};

#endif