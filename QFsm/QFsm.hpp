#ifndef QFSM_QFSM_HPP
#define QFSM_QFSM_HPP


#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/mpl/limits/vector.hpp>
#include <boost/mpl/vector.hpp>

#include "QFsm/Version.hpp"
#include "QFsm/Extensions/Uml.hpp"
#include "QFsm/Front/Fsm.hpp"
#include "QFsm/Front/Base/Fsm.hpp"
#include "QFsm/Front/Operations.hpp"
#include "QFsm/Front/IAction.hpp"
#include "QFsm/Front/IGuard.hpp"
#include "QFsm/Front/ILogger.hpp"

using namespace QFsm::Front::Operations;

namespace QFsm
{

template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_MPL_LIMIT_VECTOR_SIZE, typename T, mpl_::na)>
struct TransitionTable : boost::mpl::vector<BOOST_PP_ENUM_PARAMS(BOOST_MPL_LIMIT_VECTOR_SIZE, T)>
{ };

template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_MPL_LIMIT_VECTOR_SIZE, typename T, mpl_::na)>
struct InitialState : boost::mpl::vector<BOOST_PP_ENUM_PARAMS(BOOST_MPL_LIMIT_VECTOR_SIZE, T)>
{ };

} // namespace QFsm

#endif

