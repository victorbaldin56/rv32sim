// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Registry for storing RISCV instruction handles.

#pragma once

#include <cstdint>
#include <memory>
#include <tuple>
#include <unordered_map>

#include "instruction.hh"

namespace rv32 {

class InstructionsRegistry {
 public:
  void add(std::unique_ptr<IInstruction> inst);
  const IInstruction* get(RawInstruction raw) const noexcept;

  class Error : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

 private:
  template <typename V>
  struct ToMaps;

  template <typename V>
  using ToMapsT = ToMaps<V>::Type;

  template <typename Opcode>
  using Map = std::unordered_map<Opcode, std::unique_ptr<IInstruction>,
                                 ExtendedOpcodeHash<Opcode>>;

  template <typename... Opcodes>
  struct ToMaps<std::tuple<Opcodes...>> {
    using Type = std::tuple<Map<Opcodes>...>;
  };

  using Maps = ToMapsT<ExtendedOpcodeTuple>;

  Maps maps_;

  template <typename V>
  bool tryAddInstruction(const V& ext_opcode,
                         std::unique_ptr<IInstruction>& instruction);

  template <typename Tuple, std::size_t... Indexes>
  const IInstruction* findExtendedOpcode(
      const Tuple& ext_opcodes, std::index_sequence<Indexes...>) const noexcept;
  template <typename Tuple, std::size_t Index>
  const IInstruction* findInMap(const Tuple& ext_opcodes) const noexcept;
};
}
