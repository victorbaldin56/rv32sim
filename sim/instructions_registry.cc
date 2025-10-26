#include "sim/instructions_registry.hh"

namespace rv32 {

void InstructionsRegistry::add(std::unique_ptr<IInstruction>& inst) {
  using namespace std::string_literals;

  ExtendedOpcode ext_opcode = inst->getExtendedOpcode();
  if (!tryAddInstruction(ext_opcode, inst)) {
    // instruction still owned here if not added
    auto name = inst->getName();
    throw Error("Failed to add instruction \""s + name + "\": already exists"s);
  }
}

const IInstruction* InstructionsRegistry::get(
    RawInstruction raw) const noexcept {
  ExtendedOpcodeTuple ext_opcodes = ExtendedOpcodesCreator::create(raw);
  return findExtendedOpcode(
      ext_opcodes,
      std::make_index_sequence<std::tuple_size_v<decltype(ext_opcodes)>>());
}

template <typename V>
bool InstructionsRegistry::tryAddInstruction(
    const V& ext_opcode, std::unique_ptr<IInstruction>& instruction) {
  bool inserted = false;

  std::visit(
      [&](const auto& key) {
        using KeyT = std::decay_t<decltype(key)>;
        auto& registry = std::get<Map<KeyT>>(maps_);
        auto [it2, ins] = registry.emplace(key, std::move(instruction));
        inserted = ins;
      },
      ext_opcode);

  return inserted;
}

template <typename Tuple, std::size_t... Indexes>
const IInstruction* InstructionsRegistry::findExtendedOpcode(
    const Tuple& ext_opcodes, std::index_sequence<Indexes...>) const noexcept {
  const IInstruction* result = nullptr;

  // search for first match and return
  (void)(((result = findInMap<Tuple, Indexes>(ext_opcodes)) == nullptr) && ...);
  return result;
}

template <typename Tuple, std::size_t Index>
const IInstruction* InstructionsRegistry::findInMap(
    const Tuple& ext_opcodes) const noexcept {
  const auto& map = std::get<Index>(maps_);
  auto it = map.find(std::get<Index>(ext_opcodes));

  if (it != map.cend()) {
    return it->second.get();
  }
  return nullptr;
}
}
