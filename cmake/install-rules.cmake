install(
    TARGETS rock_paper_scissors_exe
    RUNTIME COMPONENT rock_paper_scissors_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
