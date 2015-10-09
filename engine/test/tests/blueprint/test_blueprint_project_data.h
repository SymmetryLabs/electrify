#pragma once

string serializedProject = R"({
    "value0": {
        "polymorphic_id": 2147483649,
        "polymorphic_name": "BlueprintProject",
        "ptr_wrapper": {
            "valid": 1,
            "data": {
                "Project": {},
                "blueprint": {
                    "polymorphic_id": 1073741824,
                    "ptr_wrapper": {
                        "id": 2147483649,
                        "data": {
                            "CompoundNodeHandle": {
                                "NodeHandle": {
                                    "nodeName": "BlueprintNode",
                                    "name": "Blueprint"
                                },
                                "subnodes": [
                                    {
                                        "polymorphic_id": 2147483650,
                                        "polymorphic_name": "CompoundNodeHandle",
                                        "ptr_wrapper": {
                                            "id": 2147483650,
                                            "data": {
                                                "NodeHandle": {
                                                    "nodeName": "CompoundNode",
                                                    "name": "Compound node"
                                                },
                                                "subnodes": [
                                                    {
                                                        "polymorphic_id": 1073741824,
                                                        "ptr_wrapper": {
                                                            "id": 2147483651,
                                                            "data": {
                                                                "nodeName": "ConstantColorNode",
                                                                "name": "Constant color"
                                                            }
                                                        }
                                                    },
                                                    {
                                                        "polymorphic_id": 1073741824,
                                                        "ptr_wrapper": {
                                                            "id": 2147483652,
                                                            "data": {
                                                                "nodeName": "TranslateNode",
                                                                "name": "Translate"
                                                            }
                                                        }
                                                    }
                                                ],
                                                "nodeWires": [
                                                    {
                                                        "ptr_wrapper": {
                                                            "id": 2147483653,
                                                            "data": {
                                                                "sourceHandle": {
                                                                    "locked_ptr": {
                                                                        "polymorphic_id": 1073741824,
                                                                        "ptr_wrapper": {
                                                                            "id": 3
                                                                        }
                                                                    }
                                                                },
                                                                "sourceName": "output",
                                                                "destinationHandle": {
                                                                    "locked_ptr": {
                                                                        "polymorphic_id": 1073741824,
                                                                        "ptr_wrapper": {
                                                                            "id": 4
                                                                        }
                                                                    }
                                                                },
                                                                "destinationName": "ContextModifierNode"
                                                            }
                                                        }
                                                    },
                                                    {
                                                        "ptr_wrapper": {
                                                            "id": 2147483654,
                                                            "data": {
                                                                "sourceHandle": {
                                                                    "locked_ptr": {
                                                                        "polymorphic_id": 1073741824,
                                                                        "ptr_wrapper": {
                                                                            "id": 4
                                                                        }
                                                                    }
                                                                },
                                                                "sourceName": "ContextModifierNode",
                                                                "destinationHandle": {
                                                                    "locked_ptr": {
                                                                        "polymorphic_id": 2,
                                                                        "ptr_wrapper": {
                                                                            "id": 2
                                                                        }
                                                                    }
                                                                },
                                                                "destinationName": "color"
                                                            }
                                                        }
                                                    },
                                                    {
                                                        "ptr_wrapper": {
                                                            "id": 2147483655,
                                                            "data": {
                                                                "sourceHandle": {
                                                                    "locked_ptr": {
                                                                        "polymorphic_id": 2,
                                                                        "ptr_wrapper": {
                                                                            "id": 2
                                                                        }
                                                                    }
                                                                },
                                                                "sourceName": "color",
                                                                "destinationHandle": {
                                                                    "locked_ptr": {
                                                                        "polymorphic_id": 2147483651,
                                                                        "polymorphic_name": "Blueprint",
                                                                        "ptr_wrapper": {
                                                                            "id": 1
                                                                        }
                                                                    }
                                                                },
                                                                "destinationName": "color"
                                                            }
                                                        }
                                                    }
                                                ]
                                            }
                                        }
                                    }
                                ],
                                "nodeWires": []
                            }
                        }
                    }
                }
            }
        }
    }
})";
